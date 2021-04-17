/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>        // Needed for SDL2 audio driver

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/

#include "Fluidsynth_class.h"

/*-----------------------------------------------------------------*\
|*------------------------ CFluidSynth ----------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Initialize member variables to default values.
|* Input:   N/A
|* Output:  N/A
\*-----------------------------------------------------------------*/
CFluidSynth::CFluidSynth( const char *ipInstanceName )
{
    m_pSynth                        = NULL;
    m_pAudioDriver                  = NULL;
    m_pSequencer                    = NULL;
    m_pSettings                     = NULL;
    m_bSDLActive                    = false;
    m_iSynthDest                    = -1;
    m_iClientDest                   = -1;
    m_iStartTimeOfNextPattern       = 0;

    m_pInstanceName                 = ipInstanceName;

    m_iNumInstruments = 0;
}

/*-----------------------------------------------------------------*\
|*----------------------- ~CFluidSynth ----------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Free the resources allocated by this instance before    |
|*          being destroyed.                                        |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
CFluidSynth::~CFluidSynth()
{
    Reset();
}

/*-----------------------------------------------------------------*\
|*--------------------------- Reset -------------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Reset the SDL2 and fluidsynth libraries.                |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::Reset()
{
    if ( m_pAudioDriver ) {
        delete_fluid_audio_driver(m_pAudioDriver);
        m_pAudioDriver = NULL;
    }
    if ( m_pSequencer ) {
        delete_fluid_sequencer(m_pSequencer);
        m_pSequencer = NULL;
    }
    if ( m_pSynth ) {
        delete_fluid_synth(m_pSynth);
        m_pSynth = NULL;
    }
    if ( m_pSettings ) {
        delete_fluid_settings(m_pSettings);
        m_pSettings = NULL;
    }
    if ( m_bSDLActive) {
        SDL_Quit();
        m_bSDLActive = false;
    }
}

/*-----------------------------------------------------------------*\
|*------------------------ StartInit ------------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Initialize SDL2 audio driver and fluidsynth library. If |
|*          this instance has already been initialized, reset the   |
|*          SDL2 nd fluidsynth libraries in order to initialize them| 
|*          again.                                                  |
|* Input:   N/A                                                     |
|* Output:  Returns 0 on success, non-zero for failure.             |
\*-----------------------------------------------------------------*/
int CFluidSynth::StartInit()
{
    Reset();

    // Initialize SDL2 driver
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    	printf("Unable to initialize SDL2: %s", SDL_GetError());
    	return 10;
    }

    m_bSDLActive = true;

    const char *audioDrivers[] = { "sdl2", NULL };
    if ( fluid_audio_driver_register(audioDrivers) != FLUID_OK ) {
        printf("Could not register SDL2 audio driver\n");
        return 20;
    }

    m_pSettings = new_fluid_settings();
    if ( m_pSettings == NULL ) {
        printf("Could not create fluidsynth settings structure\n");
        return 30;
    }

    m_pSynth = new_fluid_synth(m_pSettings);
    if ( fluid_settings_setstr(m_pSettings, "audio.driver", "sdl2") != FLUID_OK ) {
        printf("Could not select SDL2 audio driver\n");
        return 40;
    }

    return 0;
}

/*-----------------------------------------------------------------*\
|*------------------------ FinishInit -----------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Initialize the sequencer and register the user-provided |
|*          callback function. This should be called after StartInit|
|*          and after setting up the MIDI channels.                 |
|* Input:   N/A                                                     |
|* Output:  Returns 0 on success, non-zero for failure.             |
\*-----------------------------------------------------------------*/
int CFluidSynth::FinishInit()
{
    if ( !m_bSDLActive || !m_pSettings || !m_pSynth ) {
        printf("FluidSynth not yet initialized! Call StartInit() first.\n");
        return 50;
    }

    m_pSequencer = new_fluid_sequencer2(0);
    if ( !m_pSequencer ) {
        printf("Could not initialize sequencer.\n");
        return 60;
    }

    /* register the synth with the sequencer */
    m_iSynthDest =
        fluid_sequencer_register_fluidsynth(m_pSequencer, m_pSynth);

    /* register the client name and callback */
    m_iClientDest =
        fluid_sequencer_register_client(
            m_pSequencer,
            m_pInstanceName,
            ScheduleCallback,
            this);

    m_pAudioDriver = new_fluid_audio_driver(m_pSettings, m_pSynth);
    if ( !m_pAudioDriver ) {
        printf("Could not create audio driver.\n");
        return 70;
    }

    return 0;
}

/*-----------------------------------------------------------------*\
|*------------------------ ScheduleNoteOn -------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Schedule a note on message to play sound.               |
|* Input:   int chan, short key, unsigned int ticks                 |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::ScheduleNoteOn(
    const int                     &iChannel,
    const short                   &iKey,
    const short                   &iVelocity,
    const unsigned int            &iTime)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, m_iSynthDest);
    fluid_event_noteon(ev, iChannel, iKey, iVelocity);
    fluid_sequencer_send_at(m_pSequencer, ev, iTime, 1);
    delete_fluid_event(ev);
}

/*-----------------------------------------------------------------*\
|*------------------------ ScheduleNoteOff ------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Schedule a note off message to stop playing sound.      |
|* Input:   int chan, short key, unsigned int ticks                 |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::ScheduleNoteOff(
    const int                     &iChannel,
    const short                   &iKey,
    const unsigned int            &iTime)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, m_iSynthDest);
    fluid_event_noteoff(ev, iChannel, iKey);
    fluid_sequencer_send_at(m_pSequencer, ev, iTime, 1);
    delete_fluid_event(ev);
}

/*-----------------------------------------------------------------*\
|*------------------------ ScheduleTimerEvent ---------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Schedule a timer event (triggers the callback).         |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::ScheduleTimerEvent(void)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, m_iClientDest);
    fluid_event_timer(ev, NULL);
    fluid_sequencer_send_at(m_pSequencer, ev, m_iStartTimeOfNextPattern, 1);
    delete_fluid_event(ev);
}

/*-----------------------------------------------------------------*\
|*------------------------ ScheduleCallback -----------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Define the callback function that fluidsynth calls at   |
|*          the specified time.                                     |
|* Input:   Data passed to this class from fluidsynth               |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::ScheduleCallback(
    unsigned int                    iCurrentTime,
    fluid_event_t                   *ipEvent,
    fluid_sequencer_t               *ipSeq,
    void                            *ipData )
{
    CFluidSynth *pFluidObj = (CFluidSynth *)ipData;

    pFluidObj->ScheduleTimerEvent();
    pFluidObj->m_pSchedulePattern(
        pFluidObj->m_pPatternData,
        pFluidObj->m_iStartTimeOfNextPattern );
}

/*-----------------------------------------------------------------*\
|*------------------------ RegisterInstrument ---------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Load the specified sound font file, and then assign it  |
|*          to the next available MIDI channel.                     |
|* Input:   Sound font file                                         |
|* Output:  Returns -1 on failure, assigned MIDI channel on success |
\*-----------------------------------------------------------------*/
int CFluidSynth::RegisterInstrument( const char *ipPathToSFFile )
{
    int channel = m_iNumInstruments;
    int soundFontID = fluid_synth_sfload(m_pSynth, ipPathToSFFile, 0);

    if ( soundFontID == FLUID_FAILED ) {
        return -1;
    }

    if ( fluid_synth_program_select(
             m_pSynth,
             channel,
             soundFontID,
             0,
             0 ) != FLUID_OK ) {
        return -1;
    }

    m_iNumInstruments++;
    return channel;
}

/*-----------------------------------------------------------------*\
|*----------------------- SetCallbackFunction ---------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the callback function to be called by this class    |
|*          when the ScheduleCallback function is called by         |
|*          fluidsynth.                                             |
|* Input:   Function pointer to desired callback function           |
|*          Data to be passed to the callback function              |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::SetCallbackFunction(
    ptSchedulePattern           ipSchedulePattern,
    void                        *pData)
{
    m_pSchedulePattern      = ipSchedulePattern;
    m_pPatternData          = pData;
}

/*-----------------------------------------------------------------*\
|*------------------------- BeginPlayback -------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Call the desired callback function to begin scheduling  |
|*          notes to be played.                                     |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::BeginPlayback()
{
    /* get the current time in ticks */
    m_iStartTimeOfNextPattern = fluid_sequencer_get_tick(m_pSequencer);

    m_pSchedulePattern(m_pPatternData, m_iStartTimeOfNextPattern);
    ScheduleTimerEvent();
    m_pSchedulePattern(m_pPatternData, m_iStartTimeOfNextPattern);
}

/*-----------------------------------------------------------------*\
|*----------------------- SetMasterVolume -------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the overall volume for the synthesizer.             |
|* Input:   Gain value (range 0.0 - 10.0)                           |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void CFluidSynth::SetMasterVolume( const float &iGain )
{
    fluid_synth_set_gain(m_pSynth, iGain);
}