/*---------------------------------------------------------------------------*\
|* Title: InstrumentClave.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing clave notes.
|*
\*---------------------------------------------------------------------------*/
#ifndef FLUIDSYNTH_CLASS_H
#define FLUIDSYNTH_CLASS_H

/*---------------------------------------------------------------------------*\
|*--------------------------- FLUIDSYNTH INCLUDES ---------------------------*|
\*---------------------------------------------------------------------------*/
#include "fluidsynth.h"

/*---------------------------------------------------------------------------*\
|*---------------------------- FUNCTION POINTERS ----------------------------*|
\*---------------------------------------------------------------------------*/
typedef void (*ptSchedulePattern)(
    void                        *pData,
    unsigned int                &ioStartTimeOfNextPattern );

/*---------------------------------------------------------------------------*\
|*---------------------------- CLASS CFluidSynth ----------------------------*|
\*---------------------------------------------------------------------------*/
class CFluidSynth {
public:
    CFluidSynth( const char *ipInstanceName );
    virtual ~CFluidSynth();

    virtual void Reset();
    virtual int StartInit();
    virtual int FinishInit();

    virtual void ScheduleNoteOn(
        const int                       &iChannel,
        const short                     &iKey,
        const unsigned int              &iTime);

    virtual void ScheduleNoteOff(
        const int                       &iChannel,
        const short                     &iKey,
        const unsigned int              &iTime);

    virtual void ScheduleTimerEvent();

    virtual void SetCallbackFunction(
        ptSchedulePattern               ipSchedulePattern,
        void                            *pData = NULL );

    virtual int RegisterInstrument( const char *ipPathToSFFile );

    virtual void BeginPlayback();

    virtual void SetMasterVolume( const float &iGain );

private:

    static void ScheduleCallback(
        unsigned int                    iCurrentTime,
        fluid_event_t                   *iEvent,
        fluid_sequencer_t               *iSeq,
        void                            *iData );

    fluid_synth_t               *m_pSynth;
    fluid_audio_driver_t        *m_pAudioDriver;
    fluid_sequencer_t           *m_pSequencer;
    fluid_settings_t            *m_pSettings;

    short                       m_iSynthDest;
    short                       m_iClientDest;

    bool                        m_bSDLActive;

    const char *                m_pInstanceName;

    unsigned int                m_iStartTimeOfNextPattern;
    int                         m_iNumInstruments;

    ptSchedulePattern           m_pSchedulePattern;
    void                        *m_pPatternData;
};

#endif
