/*---------------------------------------------------------------------------*\
|* Title: InstrumentCowbell.cpp                                               |
|* Date:  30 MARCH 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide class for playing cowbell notes.                 |
|*                                                                            |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentCowbell.h"
#include <stdio.h>

CInstrumentCowbell::CInstrumentCowbell(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iKeyFactor )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iKeyFactor )
{
    /* Create a linked list of 6 notes. Up to 6 notes per bar */
    m_pNotes = Note::CreateLinkedList(6);

    m_bFirstBar = true;
}

Note *CInstrumentCowbell::GetNotes(
    const unsigned int          &iTimeOfNextPattern,
    const int                   &iDuration,
    const int                   iBeatTimes[8] )
{
    int i = 0;
    int note_duration[6];
    int keyToPlay[6];

    int note_time = iTimeOfNextPattern; // time at time_marker represents beat 1

    Note *pCurrentNote = m_pNotes;

    SheetMusic CBar = SheetMusic(iBeatTimes);

    // beat 1      = 0
    // beat 1&     = 1
    // beat 2      = 2
    // beat 2&     = 3
    // beat 3      = 4
    // beat 3&     = 5
    // beat 4      = 6
    // beat 4&     = 7
    
    // Cowbell Hitting Every Beat
    note_time = iBeatTimes[0];
    note_duration[0] = CBar.Quarter_note(0);
    note_duration[1] = CBar.Quarter_note(0);
    note_duration[2] = CBar.Quarter_note(0);
    note_duration[3] = CBar.Quarter_note(0);
    note_duration[4] = 0;
    note_duration[5] = 0;

    keyToPlay[0]    = 39;
    keyToPlay[1]    = 39;
    keyToPlay[2]    = 39;
    keyToPlay[3]    = 39;
    keyToPlay[4]    = 39;
    keyToPlay[4]    = 39;
   /*
   // Cowbell Hitting Every Off Beat
    note_time = iBeatTimes[0];
    note_duration[0] = CBar.Half_note(0);
    note_duration[1] = CBar.Half_note(0);
    note_duration[2] = 0;
    note_duration[3] = 0;
    
    keyToPlay[0]    = 39;
    keyToPlay[1]    = 39;
    */
   /*
    if ( m_bFirstBar ) {

        note_time = iBeatTimes[0];
        note_duration[0] = CBar.Quarter_note(0);                 // from 1 to 2    (down hit)
        note_duration[1] = CBar.Quarter_note(0);                 // from 2 to 3    (up hit)
        note_duration[2] = CBar.Quarter_note(0);                 // from 3 to 4    (down hit)
        note_duration[3] = CBar.Eighth_note();                    // from 4 to 4&   (up hit)
        note_duration[4] = CBar.Eighth_note();                   // from 4& to 5   (up hit)
        note_duration[5] = 0;

        // Set key to play (36 for down, 38 for up)
        // Not sure which key is correct for these, but for now having them sound different is most important
        keyToPlay[0]    = 39; // 1;
        keyToPlay[1]    = 36; // 0;
        keyToPlay[2]    = 39; // 1;
        keyToPlay[3]    = 36; // 0;
        keyToPlay[4]    = 36; // 0;
        keyToPlay[5]    = 0; // 1;

    } else {

        note_time = iBeatTimes[0];
        note_duration[0] = CBar.Quarter_note(0);                  // from 5 to 6    (down hit)
        note_duration[1] = CBar.Eighth_note();                  // from 6 to 6&   (up hit)
        note_duration[2] = CBar.Eighth_note();                  // from 6& to 7   (up hit)
        note_duration[3] = CBar.Quarter_note(0);                 // from 7 to 8    (down hit)
        note_duration[4] = CBar.Eighth_note();                  // from 8 to 8&   (up hit)
        note_duration[5] = CBar.Eighth_note();      // from 8& to 1 on next frame    (up hit)

        // Set key to play (36 for down, 38 for up)
        // Not sure which key is correct for these, but for now having them sound different is most important
        keyToPlay[0]    = 39; // 1;
        keyToPlay[1]    = 36; // 0;
        keyToPlay[2]    = 36; // 0;
        keyToPlay[3]    = 39; // 1;
        keyToPlay[4]    = 36; // 0;
        keyToPlay[5]    = 36; // 0;
    }
    */
    m_bFirstBar = !m_bFirstBar;

    printf( "----Cowbell------\n" );
    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        printf( "Note %d on: %d\n", i+1, note_time );
        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = keyToPlay[i];
        pCurrentNote->m_iVelocity         = 127;
        pCurrentNote->m_iNoteOnTime       = note_time;

        note_time += note_duration[i];

        printf( "Note %d off: %d\n", i+1, note_time );
        pCurrentNote->m_iNoteOffTime      = note_time;
        pCurrentNote = pCurrentNote->pNext;

        i++;
    }

    return m_pNotes;
}