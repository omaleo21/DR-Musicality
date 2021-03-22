#include <stdlib.h>
#include <stdio.h>
#include "fluidsynth.h"
#include "synth/fluid_synth.h"
#include "synth/fluid_voice.h"
#include "rvoice/fluid_rvoice.h"
#include "utils/fluid_sys.h"
fluid_synth_t *synth;
fluid_audio_driver_t *audiodriver;
fluid_sequencer_t *sequencer;
short synth_destination, client_destination;
unsigned int time_marker;
/* duration of the pattern in ticks. Must be divisible by 15! */
unsigned int duration = 2760; // 4000 is 120bpm, 3000 is 160bpm
/* notes of the arpeggio */
//unsigned int notes[] = { 60, 64, 67, 72, 76, 79, 84, 79, 76, 72, 67, 64 };
unsigned int notes[] = { 60, 60, 60, 60, 60 };
/* number of notes in one pattern */
unsigned int pattern_size;

int playClave = 1;
int playCowbell = 1;
int playBongos = 1;

/* prototype */
void
sequencer_callback(unsigned int time, fluid_event_t *event,
                   fluid_sequencer_t *seq, void *data);
/* schedule a note on message */
void
schedule_noteon(int chan, short key, unsigned int ticks)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, synth_destination);
    fluid_event_noteon(ev, chan, key, 127);
    fluid_sequencer_send_at(sequencer, ev, ticks, 1);
    delete_fluid_event(ev);
}
/* schedule a note off message */
void
schedule_noteoff(int chan, short key, unsigned int ticks)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, synth_destination);
    fluid_event_noteoff(ev, chan, key);
    fluid_sequencer_send_at(sequencer, ev, ticks, 1);
    delete_fluid_event(ev);
}
/* schedule a timer event (shall trigger the callback) */
void
schedule_timer_event(void)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, client_destination);
    fluid_event_timer(ev, NULL);
    fluid_sequencer_send_at(sequencer, ev, time_marker, 1);
    delete_fluid_event(ev);
}
/* schedule the arpeggio's notes */
void
schedule_pattern(void)
{
    int i, note_time, note_duration[5];
    int j, note_time2, note_duration2[6];
    int k, note_time3, note_duration3[11], keyToPlay[11];
    int timeSlice = duration / 15; // Represents one-half beat (time between 1& and 2)

    int steps[16];

    note_time = time_marker; // time at time_marker represents beat 1
    note_time2 = time_marker;

    steps[0] = time_marker;
    // beat 1      = 0
    // beat 1&     = 1
    // beat 2      = 2
    // beat 2&     = 3
    // beat 3      = 4
    // beat 3&     = 5
    // beat 4      = 6
    // beat 4&     = 7
    // beat 5      = 8
    // beat 5&     = 9
    // beat 6      = 10
    // beat 6&     = 11
    // beat 7      = 12
    // beat 7&     = 13
    // beat 8      = 14
    // beat 8&     = 15

    for ( i = 1; i < 16; i++) {
        steps[i] = steps[i - 1] + timeSlice;
    }
    
    // Son 3-2 Clave
    //note_duration[0] = steps[3] - steps[0];                           // from 1 to 2&
    //note_duration[1] = steps[6] - steps[3];                           // from 2& to 4
    //note_duration[2] = steps[10] - steps[6];                          // from 4 to 6
    //note_duration[3] = steps[12] - steps[10];                         // from 6 to 7
    //note_duration[4] = steps[0] + duration - steps[12];               // from 7 to 1 on next frame

    // Son 2-3 Clave
    note_time = steps[2];
    note_duration[0] = steps[4] - steps[2];                             // from 2 to 3
    note_duration[1] = steps[8] - steps[4];                             // from 3 to 4
    note_duration[2] = steps[11] - steps[8];                            // from 4 to 6&
    note_duration[3] = steps[14] - steps[11];                           // from 6& to 8
    note_duration[4] = steps[2] + duration - steps[14];                 // from 8 to 2 on next frame

    if ( playClave ) {
        printf( "----Clave------\n" );

        for(i = 0; i < pattern_size; ++i)
        {
            printf( "Note %d: %d\n", i, note_time );
            schedule_noteon(1, notes[i], note_time);
            note_time += note_duration[i];
            schedule_noteoff(1, notes[i], note_time);
        }
    }

    // Bongos on 2, 4, 4.5, 6, 8, 8.5
    note_time2 = steps[2]; // Start at beat 2

    note_duration2[0] = steps[6] - steps[2]; // 1                        // from 2 to 4
    note_duration2[1] = steps[7] - steps[6]; // 1                        // from 4 to 4&
    note_duration2[2] = steps[10] - steps[7]; // 1                       // from 4& to 6
    note_duration2[3] = steps[14] - steps[10]; // 2.5                    // from 6 to 8
    note_duration2[4] = steps[15] - steps[14]; // 2.5                    // from 8 to 8&
    note_duration2[5] = steps[2] + duration - steps[15];                 // from 8& to 2 on next frame

    //note_duration = duration / pattern_size;
    if ( playBongos ) {
        printf( "----Bongos------\n" );

        for ( i = 0; i < 6; ++i )
        {
            printf( "Note %d: %d\n", i, note_time2 );
            schedule_noteon( 0, 60, note_time2 );
            note_time2 += note_duration2[i];
            schedule_noteoff( 0, 60, note_time2 );
        }
    }

    // Cowbell on 1, 2, 3, 4, 4.5, 5, 6, 6.5, 7, 8, 8.5
    note_time3 = steps[0]; // Start at beat 2
    
    note_duration3[0] = steps[2] - steps[0]; // 1                         // from 1 to 2    (down hit)
    note_duration3[1] = steps[4] - steps[2]; // 1                         // from 2 to 3    (up hit)
    note_duration3[2] = steps[6] - steps[4]; // 1                         // from 3 to 4    (down hit)
    note_duration3[3] = steps[7] - steps[6]; // 2.5                       // from 4 to 4&   (up hit)
    note_duration3[4] = steps[8] - steps[7]; // 2.5                       // from 4& to 5   (up hit)
    note_duration3[5] = steps[10] - steps[8]; // 2.5                      // from 5 to 6    (down hit)
    note_duration3[6] = steps[11] - steps[10]; // 2.5                     // from 6 to 6&   (up hit)
    note_duration3[7] = steps[12] - steps[11]; // 2.5                     // from 6& to 7   (up hit)
    note_duration3[8] = steps[14] - steps[12]; // 2.5                     // from 7 to 8    (down hit)
    note_duration3[9] = steps[15] - steps[14]; // 2.5                     // from 8 to 8&   (up hit)
    note_duration3[10] = steps[0] + duration - steps[15];                 // from 8& to 1 on next frame    (up hit)

    // Set key to play (36 for down, 38 for up)
    // Not sure which key is correct for these, but for now having them sound different is most important
    keyToPlay[0]    = 39; // 1;
    keyToPlay[1]    = 36; // 0;
    keyToPlay[2]    = 39; // 1;
    keyToPlay[3]    = 36; // 0;
    keyToPlay[4]    = 36; // 0;
    keyToPlay[5]    = 39; // 1;
    keyToPlay[6]    = 36; // 0;
    keyToPlay[7]    = 36; // 0;
    keyToPlay[8]    = 39; // 1;
    keyToPlay[9]    = 36; // 0;
    keyToPlay[10]   = 36; // 0;

    //note_duration = duration / pattern_size;
    if ( playCowbell ) {
        printf( "-----Cowbell-----\n" );

        for ( i = 0; i < 11; ++i )
        {
            printf( "Note %d: %d\n", i, note_time3 );
            schedule_noteon( 2, keyToPlay[i], note_time3 );
            note_time3 += note_duration3[i];
            schedule_noteoff( 2, keyToPlay[i], note_time3 );
        }
    }

    // Update global time for next frame
    time_marker += duration;
}
void
sequencer_callback(unsigned int time, fluid_event_t *event,
                   fluid_sequencer_t *seq, void *data)
{
    schedule_timer_event();
    schedule_pattern();
}
void
usage(char *prog_name)
{
    printf("Usage: %s soundfont.sf2 [steps [duration]]\n", prog_name);
    printf("\t(optional) steps: number of pattern notes, from 2 to %d\n",
           pattern_size);
    printf("\t(optional) duration: of the pattern in ticks, default %d\n",
           duration);
}
int
main(int argc, char *argv[])
{
    double bpm = 4.8E5 / duration;

    int n, n2, n3;
    fluid_settings_t *settings;
    settings = new_fluid_settings();
    pattern_size = sizeof(notes) / sizeof(int);
    if(argc < 2)
    {
        usage(argv[0]);
    }
    else
    {
        /* create the synth, driver and sequencer instances */
        synth = new_fluid_synth(settings);

        synth->gain = 5.0;
        /* load a SoundFont */
        n = fluid_synth_sfload(synth, "bongo.sf2", 1);
        n2 = fluid_synth_sfload(synth, "claves.sf2", 1);
        n3 = fluid_synth_sfload(synth, "cowbell.sf2", 1);
       // int retVal = fluid_synth_set_bank_offset( synth, 2, 2 );

        fluid_synth_program_select( synth, 0, 1, 0, 0 );
        fluid_synth_program_select( synth, 1, 2, 0, 0 );
        fluid_synth_program_select( synth, 2, 3, 0, 0 );

        if(n != -1 && n2 != -1 && n3 != -1)
        {
            sequencer = new_fluid_sequencer2(0);
            /* register the synth with the sequencer */
            synth_destination = fluid_sequencer_register_fluidsynth(sequencer,
                                synth);
            /* register the client name and callback */
            client_destination = fluid_sequencer_register_client(sequencer,
                             "arpeggio", sequencer_callback, NULL);
            if(argc > 2)
            {
                n = atoi(argv[2]);
                if((n > 1) && (n <= pattern_size))
                {
                    pattern_size = n;
                }
            }
            if(argc > 3)
            {
                n = atoi(argv[3]);
                if(n > 0)
                {
                    duration = n;
                }
            }
            audiodriver = new_fluid_audio_driver(settings, synth);
            /* get the current time in ticks */
            time_marker = fluid_sequencer_get_tick(sequencer);
            /* schedule patterns */
            schedule_pattern();
            schedule_timer_event();
            schedule_pattern();
            /* wait for user input */
            printf("press <Enter> to stop\n");
            while ( n != 'q' ) {
                n = getchar();

                if ( n == 'b' ) {
                    playBongos = !playBongos;
                }
                if ( n == 'c' ) {
                    playClave = !playClave;
                }
                if ( n == 'w' ) {
                    playCowbell = !playCowbell;
                }
            }

        }
        /* clean and exit */
        delete_fluid_audio_driver(audiodriver);
        delete_fluid_sequencer(sequencer);
        delete_fluid_synth(synth);
    }
    delete_fluid_settings(settings);
    return 0;
}