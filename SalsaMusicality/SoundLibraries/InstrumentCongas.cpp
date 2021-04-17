/*---------------------------------------------------------------------------*\
|* Title: InstrumentCongas.cpp                                                |
|* Date:  30 MARCH 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide class for playing bongo notes.                   |
|*                                                                            |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentCongas.h"
#include <stdio.h>

CInstrumentCongas::CInstrumentCongas(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iRhythm )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iRhythm )
{
    /* Create a linked list of 3 notes. 3 notes per bar */
    m_pNotes = Note::CreateLinkedList(8);
    m_bFirstBar = true;
}

Note *CInstrumentCongas::GetNotes(
    const int                   iBeatTimes[8],
    const SharedInstrumentData  *ipSharedData )
{
    int i = 0;

    Note *pCurrentNote = m_pNotes;

    switch (m_iRhythm){
        case 1:
            N = Basic_Sym(N,iBeatTimes);
            break;
        case 2:
            N = Basic_Sym(N,iBeatTimes);
            break;
        // Case 3 and 4 are Clave Invariant
        case 3:
            N = Basic_Asym(N,iBeatTimes,m_bFirstBar);
            m_bFirstBar = !m_bFirstBar;
            break;
        case 4:
            N = Basic_Asym(N,iBeatTimes,m_bFirstBar);
            m_bFirstBar = !m_bFirstBar;
            break;
        case 5:
            N = Advanced_Asym(N,iBeatTimes,m_bFirstBar);
            m_bFirstBar = !m_bFirstBar;
            break;
        case 6:
            m_bFirstBar = !m_bFirstBar;
            N = Advanced_Asym(N,iBeatTimes,m_bFirstBar);
            break;
    }

    
    /*
    // beat 1      = 0
    // beat 1&     = 1
    // beat 2      = 2
    // beat 2&     = 3
    // beat 3      = 4
    // beat 3&     = 5
    // beat 4      = 6
    // beat 4&     = 7
    
    // Basic Conga Symmetric
    note_time = iBeatTimes[2];
    note_duration[0] = CBar.Half_note(0);                             // from 2 to 4
    note_duration[1] = CBar.Eighth_note();                             // from 4 to 4.5
    note_duration[2] = CBar.Eighth_note()+CBar.Half_note(0);                             // from 4.5 to 2
    note_duration[3] = 0;
    note_duration[4] = 0;

   // Basic Conga Asymmetric
   if ( m_bFirstBar ) {
        note_time = iBeatTimes[6];
        note_duration[0] = CBar.Whole_note(0);                             // from 4 to 8
        note_duration[1] = 0;                                
        note_duration[2] = 0;
        note_duration[3] = 0;
        note_duration[4] = 0;
    } else {
        note_time = iBeatTimes[6];
        note_duration[0] = CBar.Eighth_note();                            // from 5 to 6&
        note_duration[1] = CBar.Whole_note(0)-CBar.Eighth_note();                            // from 6& to 8
        note_duration[2] = 0;                 
        note_duration[3] = 0;
        note_duration[4] = 0;
    }

   // Advanced Conga 
   if ( m_bFirstBar ) {
        note_time = iBeatTimes[2];
        note_duration[0] = CBar.Half_note(0);                             // from 2 to 4
        note_duration[1] = CBar.Eighth_note();                             // from 4 to 4.5
        note_duration[2] = CBar.Eighth_note()+CBar.Half_note(0);                             // from 4.5 to 6
        note_duration[3] = 0;
        note_duration[4] = 0;
    } else {
        note_time = iBeatTimes[2];
        note_duration[0] = CBar.Eighth_note();                            // from 6 to 6&
        note_duration[1] = CBar.Eighth_note();                            // from 6& to 7
        note_duration[2] = CBar.Quarter_note(0);                 // from 7 to 8 on next frame
        note_duration[3] = CBar.Eighth_note();  // 8 to 8&
        note_duration[4] = CBar.Eighth_note()+CBar.Half_note(0); // from 8.5 to 2
    }

    
    */


    printf( "----Congas------\n" );
    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !N.note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        printf( "Note %d on: %d\n", i+1, N.note_time );
        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = N.keytoplay[i];
        pCurrentNote->m_iVelocity         = 127;
        pCurrentNote->m_iNoteOnTime       = N.note_time;

        N.Update_start(N.note_duration[i]);
        printf( "Note %d off: %d\n", i+1, N.note_time );
        pCurrentNote->m_iNoteOffTime      = N.note_time;
        pCurrentNote = pCurrentNote->pNext;

        i++;
    }

    return m_pNotes;
}

Note_structure CInstrumentCongas::Basic_Sym(Note_structure N, const int iBeatTimes[8])
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    time = iBeatTimes[2];
    duration[0] = CBar.Half_note(0);                             // from 2 to 4
    duration[1] = CBar.Eighth_note();                             // from 4 to 4.5
    duration[2] = CBar.Eighth_note()+CBar.Half_note(0);                             // from 4.5 to 2

    keys[0] = 64;
    keys[1] = 62;
    keys[2] = 62;

    N.Set(time,duration,keys);

    return (N);
}

Note_structure CInstrumentCongas::Basic_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar)
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    if ( m_bFirstBar ) {
        time = iBeatTimes[6];
        duration[0] = CBar.Whole_note(0);                             // from 4 to 8
        keys[0] = 62;
    } else {
        time = iBeatTimes[6];
        duration[0] = CBar.Eighth_note();                            // from 5 to 6&
        duration[1] = CBar.Whole_note(0)-CBar.Eighth_note();                            // from 6& to 8
        keys[1] = 62;
        keys[2] = 62;
    }

    N.Set(time,duration,keys);

    return (N);
}
/*
Note_structure CInstrumentCongas::Advanced_Full(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar)
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    if ( m_bFirstBar ) {
        time = iBeatTimes[2];
        duration[0] = CBar.Half_note(0);                             // from 2 to 4
        duration[1] = CBar.Eighth_note();                             // from 4 to 4.5
        duration[2] = CBar.Eighth_note()+CBar.Half_note(0);                             // from 4.5 to 6
        keys[0] = 64;
        keys[1] = 62;
        keys[2] = 62;

    } else {
        time = iBeatTimes[2];
        duration[0] = CBar.Eighth_note();                            // from 6 to 6&
        duration[1] = CBar.Eighth_note();                            // from 6& to 7
        duration[2] = CBar.Quarter_note(0);                 // from 7 to 8 on next frame
        duration[3] = CBar.Eighth_note();  // 8 to 8&
        duration[4] = CBar.Eighth_note()+CBar.Half_note(0); // from 8.5 to 2
        keys[0] = 64;
        keys[1] = 62;
        keys[2] = 62;
        keys[3] = 62;
        keys[4] = 62;
    }
    
    N.Set(time,duration,keys);

    return (N);
}
*/
Note_structure CInstrumentCongas::Advanced_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar)
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    if ( m_bFirstBar ) {
        time = iBeatTimes[2];
        duration[0] = CBar.Half_note(0);                             // from 2 to 4
        duration[1] = CBar.Eighth_note();                             // from 4 to 4.5
        duration[2] = CBar.Eighth_note()+CBar.Half_note(0);                             // from 4.5 to 6
        keys[0] = 64;
        keys[1] = 62;
        keys[2] = 62;

    } else {
        time = iBeatTimes[2];
        duration[0] = CBar.Eighth_note();                            // from 6 to 6&
        duration[1] = CBar.Eighth_note();                            // from 6& to 7
        duration[2] = CBar.Quarter_note(0);                 // from 7 to 8 on next frame
        duration[3] = CBar.Eighth_note();  // 8 to 8&
        duration[4] = CBar.Eighth_note()+CBar.Half_note(0); // from 8.5 to 2
        keys[0] = 64;
        keys[1] = 62;
        keys[2] = 62;
        keys[3] = 62;
        keys[4] = 62;
    }
    
    N.Set(time,duration,keys);

    return (N);
}