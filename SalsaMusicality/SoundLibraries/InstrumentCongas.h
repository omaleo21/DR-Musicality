/*---------------------------------------------------------------------------*\
|* Title: InstrumentCongas.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing bongo notes.
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_CONGAS_H
#define INSTRUMENT_CONGAS_H

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBase.h"
#include "SheetMusic.h"

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentCongas : public virtual CInstrumentBase
{
public:
    CInstrumentCongas(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iRhythm );

    virtual ~CInstrumentCongas() {};

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

private:
    bool m_bFirstBar;

    Note_structure N;

    Note_structure Basic_Sym(Note_structure N, const int iBeatTimes[8]);

    Note_structure Basic_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar);

    Note_structure Advanced_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar);
};

#endif