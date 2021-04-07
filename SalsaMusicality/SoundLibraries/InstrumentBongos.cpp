/*---------------------------------------------------------------------------*\
|* Title: InstrumentBongos.cpp
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing bongo notes.
|*
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBongos.h"
#include <stdio.h>

CInstrumentBongos::CInstrumentBongos(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iKeyFactor )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iKeyFactor )
{
    /* Create a linked list of 3 notes. 3 notes per bar */
    m_pNotes = Note::CreateLinkedList(3);
}

Note *CInstrumentBongos::GetNotes(
    const unsigned int          &iTimeOfNextPattern,
    const int                   &iDuration,
    const int                   iBeatTimes[8] )
{
    int i = 0;
    int note_duration[3];

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

    // Basic conga - bar 1 = bar 2
    note_time = iBeatTimes[2];
    note_duration[0] = iBeatTimes[6] - iBeatTimes[2];                             // from 2 to 3
    note_duration[1] = iBeatTimes[7] - iBeatTimes[6];                             // from 2 to 3
    note_duration[2] = iBeatTimes[2] + iDuration - iBeatTimes[7];                             // from 3 to 5

    printf( "----Bongos------\n" );
    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        printf( "Note %d on: %d\n", i, note_time );
        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = 60;
        pCurrentNote->m_iNoteOnTime       = note_time;

        note_time += note_duration[i];

        printf( "Note %d off: %d\n", i, note_time );
        pCurrentNote->m_iNoteOffTime      = note_time;
        pCurrentNote = pCurrentNote->pNext;

        i++;
    }

    return m_pNotes;
}