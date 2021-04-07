/*---------------------------------------------------------------------------*\
|* Title: InstrumentClave.cpp
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing clave notes.
|*
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentClave.h"
#include <stdio.h>

CInstrumentClave::CInstrumentClave(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iKeyFactor )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iKeyFactor )
{
    /* Create a linked list of 3 notes. Up to 3 notes per bar */
    m_pNotes = Note::CreateLinkedList(3);
    m_bFirstBar = true;
}

Note *CInstrumentClave::GetNotes(
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

    // Son 3-2 Clave
    //note_duration[0] = steps[3] - steps[0];                           // from 1 to 2&
    //note_duration[1] = steps[6] - steps[3];                           // from 2& to 4
    //note_duration[2] = steps[10] - steps[6];                          // from 4 to 6
    //note_duration[3] = steps[12] - steps[10];                         // from 6 to 7
    //note_duration[4] = steps[0] + duration - steps[12];               // from 7 to 1 on next frame

    // Son 2-3 Clave
    if ( m_bFirstBar ) {
        note_time = iBeatTimes[2];
        note_duration[0] = iBeatTimes[4] - iBeatTimes[2];                             // from 2 to 3
        note_duration[1] = iBeatTimes[0] + iDuration - iBeatTimes[4];                             // from 3 to 5
        note_duration[2] = 0;
    } else {
        note_time = iBeatTimes[0];
        note_duration[0] = iBeatTimes[3] - iBeatTimes[0];                            // from 5 to 6&
        note_duration[1] = iBeatTimes[6] - iBeatTimes[3];                           // from 6& to 8
        note_duration[2] = iBeatTimes[2] + iDuration - iBeatTimes[6];                 // from 8 to 2 on next frame
    }

    m_bFirstBar = !m_bFirstBar;

    printf( "----Clave------\n" );
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