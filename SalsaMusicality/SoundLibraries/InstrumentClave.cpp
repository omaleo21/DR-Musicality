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
#include "SoundLibraryInterface.h"
#include <stdio.h>

CInstrumentClave::CInstrumentClave(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iRhythm )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iRhythm )
{
    /* Create a linked list of 3 notes. Up to 3 notes per bar */
    m_pNotes = Note::CreateLinkedList(8);
    m_bFirstBar = true;
}

Note *CInstrumentClave::GetNotes(
    const int                   iBeatTimes[8],
    const SharedInstrumentData  *ipSharedData )
{
    int i = 0;

    Note *pCurrentNote = m_pNotes;
    /*
    // beat 1      = 0
    // beat 1&     = 1
    // beat 2      = 2
    // beat 2&     = 3
    // beat 3      = 4
    // beat 3&     = 5
    // beat 4      = 6
    // beat 4&     = 7
    /*
    // Son 2-3 Clave
    if ( m_bFirstBar ) {
        note_time = iBeatTimes[2];
        note_duration[0] = CBar.Quarter_note(0);                             // from 2 to 3
        note_duration[1] = CBar.Half_note(0);                                // from 3 to 5
        note_duration[2] = 0;
    } else {
        note_time = iBeatTimes[0];
        note_duration[0] = CBar.Quarter_note(1);                            // from 5 to 6&
        note_duration[1] = CBar.Quarter_note(1);                            // from 6& to 8
        note_duration[2] = CBar.Half_note(0);;                 // from 8 to 2 on next frame
    }
    
    
    // Son 2-3 Rumba Clave
    if ( m_bFirstBar ) {
        note_time = iBeatTimes[2];
        note_duration[0] = CBar.Quarter_note(0);                             // from 2 to 3
        note_duration[1] = CBar.Half_note(0);                                // from 3 to 5
        note_duration[2] = 0;
    } else {
        note_time = iBeatTimes[0];
        note_duration[0] = CBar.Quarter_note(1);                            // from 5 to 6&
        note_duration[1] = CBar.Half_note(0);                            // from 6& to 8
        note_duration[2] = CBar.Quarter_note(1);                 // from 8 to 2 on next frame
    }
    */
    
    switch (m_iRhythm){
        case CLA_SON_2_3:
            N = Son(N,iBeatTimes);
            m_bFirstBar = !m_bFirstBar;
            break;
        case CLA_SON_3_2:
            m_bFirstBar = !m_bFirstBar;
            N = Son(N,iBeatTimes);
            break;
        case CLA_RUMBA_2_3:
            N = Rumba(N,iBeatTimes);
            m_bFirstBar = !m_bFirstBar;
            break;
        case CLA_RUMBA_3_2:
            m_bFirstBar = !m_bFirstBar;
            N = Rumba(N,iBeatTimes);
            break;
    }

    if ( m_bIsEnabled ) {
        printf( "----Clave------\n" );
    }

    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !N.note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = 60;
        pCurrentNote->m_iVelocity         = 127;
        pCurrentNote->m_iNoteOnTime       = N.note_time;

        N.Update_start(N.note_duration[i]);

        pCurrentNote->m_iNoteOffTime      = N.note_time;

        if ( m_bIsEnabled ) {
            printf( "Note %d on: %d\n", i+1, pCurrentNote->m_iNoteOnTime );
            printf( "Note %d off: %d\n", i+1, pCurrentNote->m_iNoteOffTime );
        }

        pCurrentNote = pCurrentNote->pNext;

        i++;
    }

    return m_pNotes;
}

Note_structure CInstrumentClave::Son(Note_structure N, const int iBeatTimes[8])
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    if ( m_bFirstBar ) {
        time = iBeatTimes[2];
        duration[0] = CBar.Quarter_note(0);                             // from 2 to 3
        duration[1] = CBar.Half_note(0);                                // from 3 to 5

    } else {
        time = iBeatTimes[0];
        duration[0] = CBar.Quarter_note(1);                            // from 5 to 6&
        duration[1] = CBar.Quarter_note(1);                            // from 6& to 8
        duration[2] = CBar.Half_note(0);;                 // from 8 to 2 on next frame
    }

    N.Set(time,duration,keys);

    return (N);
}

Note_structure CInstrumentClave::Rumba(Note_structure N, const int iBeatTimes[8])
{   
    int time;
    int duration[8]= {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    if ( m_bFirstBar ) {
        time = iBeatTimes[2];
        duration[0] = CBar.Quarter_note(0);                             // from 2 to 3
        duration[1] = CBar.Half_note(0);                                // from 3 to 5

    } else {
        time = iBeatTimes[0];
        duration[0] = CBar.Quarter_note(1);                            // from 5 to 6&
        duration[1] = CBar.Half_note(0);                            // from 6& to 8&
        duration[2] = CBar.Quarter_note(1);                       // from 8& to 2 on next frame

    }

    N.Set(time,duration,keys);

    return (N);
}

void CInstrumentClave::UpdateSharedData(
    const int                   iBeatTimes[8],
    SharedInstrumentData        *iopSharedData )
{
    bool isNextFrameFirstBar = m_bFirstBar;
    
    /* Determine whether the next notes to be played will be on the first bar.          *\
    \* The 3-2 claves negate m_bFirstBar before scheduling notes, so do the same here.  */
    switch (m_iRhythm) {
        case CLA_SON_3_2:
        case CLA_RUMBA_3_2:
            isNextFrameFirstBar = !isNextFrameFirstBar;
            break;
        default:
            break;
    }
    
    /* Assign number of clave hits for the next bar. */
    if ( isNextFrameFirstBar ) {
        iopSharedData->Update_Clave(true);
    } else {
        iopSharedData->Update_Clave(false);
    }
}