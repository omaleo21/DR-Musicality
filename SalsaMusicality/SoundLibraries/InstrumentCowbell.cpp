/*---------------------------------------------------------------------------*\
|* Title: InstrumentCowbell.cpp
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing cowbell notes.
|*
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

    // beat 1      = 0
    // beat 1&     = 1
    // beat 2      = 2
    // beat 2&     = 3
    // beat 3      = 4
    // beat 3&     = 5
    // beat 4      = 6
    // beat 4&     = 7

    if ( m_bFirstBar ) {

        note_time = iBeatTimes[0];
        note_duration[0] = iBeatTimes[2] - iBeatTimes[0];                 // from 1 to 2    (down hit)
        note_duration[1] = iBeatTimes[4] - iBeatTimes[2];                 // from 2 to 3    (up hit)
        note_duration[2] = iBeatTimes[6] - iBeatTimes[4];                 // from 3 to 4    (down hit)
        note_duration[3] = iBeatTimes[7] - iBeatTimes[6];                 // from 4 to 4&   (up hit)
        note_duration[4] = iBeatTimes[0] + iDuration - iBeatTimes[7];     // from 4& to 5   (up hit)
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
        note_duration[0] = iBeatTimes[2] - iBeatTimes[0];                 // from 5 to 6    (down hit)
        note_duration[1] = iBeatTimes[3] - iBeatTimes[2];                 // from 6 to 6&   (up hit)
        note_duration[2] = iBeatTimes[4] - iBeatTimes[3];                 // from 6& to 7   (up hit)
        note_duration[3] = iBeatTimes[6] - iBeatTimes[4];                 // from 7 to 8    (down hit)
        note_duration[4] = iBeatTimes[7] - iBeatTimes[6];                 // from 8 to 8&   (up hit)
        note_duration[5] = iBeatTimes[0] + iDuration - iBeatTimes[7];     // from 8& to 1 on next frame    (up hit)

        // Set key to play (36 for down, 38 for up)
        // Not sure which key is correct for these, but for now having them sound different is most important
        keyToPlay[0]    = 39; // 1;
        keyToPlay[1]    = 36; // 0;
        keyToPlay[2]    = 36; // 0;
        keyToPlay[3]    = 39; // 1;
        keyToPlay[4]    = 36; // 0;
        keyToPlay[5]    = 36; // 0;
    }

    m_bFirstBar = !m_bFirstBar;

    printf( "----Cowbell------\n" );
    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        printf( "Note %d on: %d\n", i, note_time );
        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = keyToPlay[i];
        pCurrentNote->m_iNoteOnTime       = note_time;

        note_time += note_duration[i];

        printf( "Note %d off: %d\n", i, note_time );
        pCurrentNote->m_iNoteOffTime      = note_time;
        pCurrentNote = pCurrentNote->pNext;

        i++;
    }

    return m_pNotes;
}