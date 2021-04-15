/*---------------------------------------------------------------------------*\
|* Title: InstrumentBongos.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing bongo notes.
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_BONGOS_H
#define INSTRUMENT_BONGOS_H

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBase.h"
#include "SheetMusic.h"

/*---------------------------------------------------------------------------*\
|*--------------------------- NOTE STRUCTURE --------------------------------*|
\*---------------------------------------------------------------------------*/

struct Note_structure{
        int note_time;
        int note_duration[5];

        void Set(int start_time, int duration[5])
        {
            note_time = start_time;
            for(int i = 0; i < 5; i++) {
                note_duration[i] = duration[i];
            } 
        }

        void Update_start(int additional_time)
            {note_time += additional_time;
            }
    };

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentBongos : public virtual CInstrumentBase
{
public:
    CInstrumentBongos(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iKeyFactor );

    virtual ~CInstrumentBongos() {};

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

private:
    bool m_bFirstBar;
    short m_iRhythm;

    Note_structure N;

    Note_structure Basic_Sym(Note_structure N, const int iBeatTimes[8]);

    Note_structure Basic_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar);
};

#endif