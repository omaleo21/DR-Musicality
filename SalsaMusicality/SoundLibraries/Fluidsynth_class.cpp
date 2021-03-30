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
CFluidSynth::CFluidSynth(
    const char                  *ipInstanceName,
    fluid_event_callback_t      ipCallbackFunc )
{
    m_pSynth            = NULL;
    m_pAudioDriver      = NULL;
    m_pSequencer        = NULL;
    m_pSettings         = NULL;
    m_bSDLActive        = false;
    m_iSynthDest        = -1;
    m_iClientDest       = -1;

    m_pInstanceName     = ipInstanceName;
    m_pCallbackFunc     = ipCallbackFunc;
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
            m_pCallbackFunc,
            NULL);

    m_pAudioDriver = new_fluid_audio_driver(m_pSettings, m_pSynth);
    if ( !m_pAudioDriver ) {
        printf("Could not create audio driver.\n");
        return 70;
    }

    return 0;
}