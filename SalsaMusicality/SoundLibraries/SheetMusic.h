/*---------------------------------------------------------------------------*\
|* Title: SheetMusic.h                                                    |
|* Date:  10 APRIL 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide a class that contains note lengths.              |                                                   |
\*---------------------------------------------------------------------------*/
#ifndef SHEET_MUSIC_H
#define SHEET_MUSIC_H

/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/

#include <string.h>

/*---------------------------------------------------------------------------*\
|*--------------------------- NOTE STRUCTURE --------------------------------*|
\*---------------------------------------------------------------------------*/

struct Note_structure{
        int note_time;
        int note_duration[8];
        int keytoplay[8];

        void Set(int start_time, int duration[8], int keys[8])
        {
            note_time = start_time;
            for(int i = 0; i < 8; i++) {
                note_duration[i] = duration[i];
                keytoplay[i] = keys[i];
            } 
        }

        void Update_start(int additional_time)
            {note_time += additional_time;
            }
};

/*---------------------------------------------------------------------------*\
|*------------------------ SHEET MUSIC CLASS --------------------------------*|
\*---------------------------------------------------------------------------*/

class SheetMusic{
    
    public:
        SheetMusic(const int iBeatTimes[8]);
        int Whole_note(bool bdot);
        int Half_note(bool bdot);
        int Quarter_note(bool bdot);
        int Eighth_note();

    private:
        int m_iBeats[8];
};

#endif