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
#include "SoundLibraryInterface.h"
#include <stdio.h>
#include <algorithm>

CInstrumentCowbell::CInstrumentCowbell(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iRhythm )
    : CInstrumentBase(
        ipPathToSoundFont,
        iIsEnabled,
        iRhythm )
{
    /* Create a linked list of 6 notes. Up to 6 notes per bar */
    m_pNotes = Note::CreateLinkedList(8);

    m_bFirstBar = true;
}

Note *CInstrumentCowbell::GetNotes(
    const int                   iBeatTimes[8],
    const SharedInstrumentData  *ipSharedData )
{
    int i = 0;

    Note *pCurrentNote = m_pNotes;

    switch (m_iRhythm){
        case COW_ALL_BEATS:
            N = All_Beats(N,iBeatTimes);
            break;
        case COW_DOWN_BEATS:
            N = Down_Beats(N,iBeatTimes);
            break;
        case COW_CLAVE_ALIGNED:
            m_bFirstBar = ipSharedData->m_bNumClaveBarHits;
            N = Clave_Aligned(N,iBeatTimes);
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

   // Cowbell Hitting Every Off Beat
    note_time = iBeatTimes[0];
    note_duration[0] = CBar.Half_note(0);
    note_duration[1] = CBar.Half_note(0);
    note_duration[2] = 0;
    note_duration[3] = 0;
    
    keyToPlay[0]    = 39;
    keyToPlay[1]    = 39;

   // Advanced_Asymmetric
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

    if ( m_bIsEnabled ) {
        printf( "----Cowbell------\n" );
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

Note_structure CInstrumentCowbell::All_Beats(Note_structure N, const int iBeatTimes[8]){
    int time;
    int duration[8]= {0};
    int keys[8];

    SheetMusic CBar = SheetMusic(iBeatTimes);

    time = iBeatTimes[0];

    std::fill(duration, keys+4, CBar.Quarter_note(0));
    std::fill(keys, keys+8, 39);
    N.Set(time,duration,keys);

    return (N);
}

Note_structure CInstrumentCowbell::Down_Beats(Note_structure N, const int iBeatTimes[8]){
    int time;
    int duration[8]= {0};
    int keys[8];

    

    SheetMusic CBar = SheetMusic(iBeatTimes);

    time = iBeatTimes[0];
    std::fill(duration, duration+2, CBar.Half_note(0));
    std::fill(keys, keys+8, 39);
    N.Set(time,duration,keys);

    return (N);
}

Note_structure CInstrumentCowbell::Clave_Aligned(Note_structure N, const int iBeatTimes[8]){
    int time;
    int duration[8]= {0};
    int keys[8] = {0};

    SheetMusic CBar = SheetMusic(iBeatTimes);

        if ( m_bFirstBar ) {

        time = iBeatTimes[0];
        duration[0] = CBar.Quarter_note(0);                 // from 1 to 2    (down hit)
        duration[1] = CBar.Quarter_note(0);                 // from 2 to 3    (up hit)
        duration[2] = CBar.Quarter_note(0);                 // from 3 to 4    (down hit)
        duration[3] = CBar.Eighth_note();                    // from 4 to 4&   (up hit)
        duration[4] = CBar.Eighth_note();                   // from 4& to 5   (up hit)
 

        // Set key to play (36 for down, 38 for up)
        // Not sure which key is correct for these, but for now having them sound different is most important
        keys[0]    = 39; // 1;
        keys[1]    = 36; // 0;
        keys[2]    = 39; // 1;
        keys[3]    = 36; // 0;
        keys[4]    = 36; // 0;

    } else {

        time = iBeatTimes[0];
        duration[0] = CBar.Quarter_note(0);                  // from 5 to 6    (down hit)
        duration[1] = CBar.Eighth_note();                  // from 6 to 6&   (up hit)
        duration[2] = CBar.Eighth_note();                  // from 6& to 7   (up hit)
        duration[3] = CBar.Quarter_note(0);                 // from 7 to 8    (down hit)
        duration[4] = CBar.Eighth_note();                  // from 8 to 8&   (up hit)
        duration[5] = CBar.Eighth_note();      // from 8& to 1 on next frame    (up hit)

        // Set key to play (36 for down, 38 for up)
        // Not sure which key is correct for these, but for now having them sound different is most important
        keys[0]    = 39; // 1;
        keys[1]    = 36; // 0;
        keys[2]    = 36; // 0;
        keys[3]    = 39; // 1;
        keys[4]    = 36; // 0;
        keys[5]    = 36; // 0;
    }

    N.Set(time,duration,keys);

    return (N);
}