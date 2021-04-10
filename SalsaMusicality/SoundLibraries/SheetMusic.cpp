/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/

#include "SheetMusic.h"

void SheetMusic::Bar(const int iBeatTimes[8])
{memcpy( m_iBeats, iBeatTimes, 8 * sizeof(int) );
}

int Whole_note(bool bdot){
    if (bdot) {
        return (m_iBeats[7]-m_iBeats[0])+(m_iBeats[3]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[7]-m_iBeats[0]);
    }
}

int Half_note(bool bdot){
    if (bdot) {
        return (m_iBeats[5]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[3]-m_iBeats[0]);
    }
}

int Quarter_note(bool bdot){
    if (bdot) {
        return (m_iBeats[3]-m_iBeats[0]);
    }
    else{
        return (m_iBeats[2]-m_iBeats[0]);
    }
}

int Eighth_note(){
    return (m_iBeats[1]-m_iBeats[0]);
}

