/*---------------------------------------------------------------------------*\
|* Title: InstrumentBongos.cpp                                                |
|* Date:  30 MARCH 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide class for playing bongo notes.                   |
|*                                                                            |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBongos.h"
#include "SoundLibraryInterface.h"

#include <stdio.h>
#include <algorithm>

CInstrumentBongos::CInstrumentBongos(
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

Note *CInstrumentBongos::GetNotes(
    const int                   iBeatTimes[8],
    const SharedInstrumentData  *ipSharedData )
{
    int i = 0;

    Note *pCurrentNote = m_pNotes;

    switch (m_iRhythm){
        case BON_ALL_BEATS:
            N = All_Beats(N,iBeatTimes);
            break;
        case BON_MARTILLO:
            N = Martillo(N, iBeatTimes);
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

    if ( m_bIsEnabled ) {
        printf( "----Bongos------\n" );
    }

    while ( pCurrentNote )
    {
        /* Set channel to -1 if note stream is finished. */
        if ( !N.note_duration[i] ) {
            pCurrentNote->m_iChannel = -1;
            break;
        }

        pCurrentNote->m_iChannel          = m_iChannel;
        pCurrentNote->m_iKey              = N.keytoplay[i];
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

Note_structure CInstrumentBongos::All_Beats(Note_structure N, const int iBeatTimes[8])
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    time = iBeatTimes[0];
    std::fill(duration, duration+4, CBar.Quarter_note(0)); // All quarter notes in a bar.

    if (m_bFirstBar){
        std::fill(keys, keys+4, 63);
    }   else {
        std::fill(keys, keys+4, 60);
    }

    N.Set(time,duration,keys);

    return (N);
}

Note_structure CInstrumentBongos::Martillo(Note_structure N, const int iBeatTimes[8])
{   
    int time;
    int duration[8] = {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);
    
    time = iBeatTimes[0];

    std::fill(duration, duration+8, CBar.Eighth_note()); // All eighth notes in a bar.

    keys[0] = 58;
    keys[1] = 86;
    keys[2] = 64;
    keys[3] = 52;
    keys[4] = 58;
    keys[5] = 86;
    keys[6] = 61;
    keys[7] = 52;
    

    N.Set(time,duration,keys);

    return (N);
}

