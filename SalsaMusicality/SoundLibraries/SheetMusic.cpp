/*---------------------------------------------------------------------------*\
|* Title: SheetMusic.cpp                                                      |
|* Date:  10 APRIL 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide a class that contains note lengths.              |                                                   |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/

#include "SheetMusic.h"

/*---------------------------------------------------------------------------*\
|*------------------------ SHEET MUSIC CLASS --------------------------------*|
\*---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------*\
|*------------------------- Bar -----------------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Initialize the beats in a bar.                          |
|* Input:   Beat times of the 8 half counts in a bar.               |
|* Output:  Array of beat times used by class.                      |
\*-----------------------------------------------------------------*/

void SheetMusic::Bar(const int iBeatTimes[8])
{memcpy( m_iBeats, iBeatTimes, 8 * sizeof(int) );
}

/*-----------------------------------------------------------------*\
|*------------------------- Whole_note ----------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Denote the time of a whole note in a bar.               |
|* Input:   Boolean to denote existance of dotted note.             |
|* Output:  Length of time of a whole note (or dotted whole note).  |
\*-----------------------------------------------------------------*/

int SheetMusic::Whole_note(bool bdot){
    if (bdot) {
        return (m_iBeats[7]-m_iBeats[0])+(m_iBeats[3]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[7]-m_iBeats[0]);
    }
}

/*-----------------------------------------------------------------*\
|*------------------------- Half_note -----------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Denote the time of a half note in a bar.                |
|* Input:   Boolean to denote existance of dotted note.             |
|* Output:  Length of time of a half note (or dotted half note).    |
\*-----------------------------------------------------------------*/

int SheetMusic::Half_note(bool bdot){
    if (bdot) {
        return (m_iBeats[5]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[3]-m_iBeats[0]);
    }
}

/*-----------------------------------------------------------------*\
|*------------------------- Quarter_note --------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Denote the time of a quarter note in a bar.             |
|* Input:   Boolean to denote existance of dotted note.             |
|* Output:  Length of time of a quarter note (or dotted quarter     |
|*          note).                                                  |
\*-----------------------------------------------------------------*/

int SheetMusic::Quarter_note(bool bdot){
    if (bdot) {
        return (m_iBeats[3]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[2]-m_iBeats[0]);
    }
}

/*-----------------------------------------------------------------*\
|*------------------------- Eighth_note ---------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Denote the time of a eighth note in a bar.              |
|* Input:   N/A                                                     |
|* Output:  Length of time of a eighth note.                        |
\*-----------------------------------------------------------------*/

int SheetMusic::Eighth_note(){
    return (m_iBeats[1]-m_iBeats[0]);
}

