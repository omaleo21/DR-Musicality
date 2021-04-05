/*---------------------------------------------------------------------------*\
|*--------------------------- FLUIDSYNTH INCLUDES ---------------------------*|
\*---------------------------------------------------------------------------*/

#include "synth/fluid_synth.h"

/*---------------------------------------------------------------------------*\
|*--------------------------- LOCAL INCLUDES --------------------------------*|
\*---------------------------------------------------------------------------*/

#include "Fluidsynth_class.h"

class Notes{
    public:
            
        Notes();

        virtual void schedule_noteon(int chan, short key, unsigned int ticks);
        virtual void schedule_noteoff(int chan, short key, unsigned int ticks);            virtual void schedule_timer_event(void);
    private:
        CFluidSynth *pFluid; 
        fluid_sequencer_t *sequencer;
        
        int chan;
        short key;
        unsigned int ticks;
};
