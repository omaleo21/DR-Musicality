/*---------------------------------------------------------------------------*\
|*--------------------------- FLUIDSYNTH INCLUDES ---------------------------*|
\*---------------------------------------------------------------------------*/
#include "fluidsynth.h"

class CFluidSynth {
public:
    CFluidSynth(
        const char *ipInstanceName,
        fluid_event_callback_t ipCallbackFunc );
    virtual ~CFluidSynth();

    virtual int StartInit();
    virtual int FinishInit();
    virtual void Reset();

    // Accessor functions
    virtual fluid_synth_t       *GetSynth()         { return m_pSynth; }
    virtual fluid_sequencer_t   *GetSequencer()     { return m_pSequencer; }
    virtual short               GetSynthDest()      { return m_iSynthDest; }
    virtual short               GetClientDest()     { return m_iClientDest; }

private:
    fluid_synth_t               *m_pSynth;
    fluid_audio_driver_t        *m_pAudioDriver;
    fluid_sequencer_t           *m_pSequencer;
    fluid_settings_t            *m_pSettings;
    fluid_event_callback_t      m_pCallbackFunc;

    short                       m_iSynthDest;
    short                       m_iClientDest;

    bool                        m_bSDLActive;

    const char *                m_pInstanceName;
};