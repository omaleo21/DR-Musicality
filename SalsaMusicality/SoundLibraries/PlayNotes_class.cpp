/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/

#include "PlayNotes_class.h"

Notes::Notes()
{
 sequencer = pFluid->GetSequencer();
}

void Notes::schedule_noteon(int chan, short key, unsigned int ticks)
{   
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, pFluid->GetSynthDest());
    fluid_event_noteon(ev, chan, key, 127);
    fluid_sequencer_send_at(sequencer, ev, ticks, 1);
    delete_fluid_event(ev);
}
