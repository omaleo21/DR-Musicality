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
    virtual void schedule_noteon(int chan, short key, unsigned int ticks);
    virtual void schedule_noteoff(int chan, short key, unsigned int ticks); 
    virtual void schedule_timer_event(void);   
    virtual unsigned int get_time_marker(void);
    virtual void set_time_marker(int duration);

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
    
    unsigned int time_marker;
};