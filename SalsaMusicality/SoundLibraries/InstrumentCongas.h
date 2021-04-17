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
        const int                   iBeatTimes[8],
        const SharedInstrumentData  *ipSharedData );

private:
    bool m_bFirstBar;

    Note_structure N;

    Note_structure Basic_Offbeat(Note_structure N, const int iBeatTimes[8]);

    Note_structure Basic_Endbeat(Note_structure N, const int iBeatTimes[8]);

    Note_structure Clave_Aligned(Note_structure N, const int iBeatTimes[8]);

    // Note_structure Advanced_Full(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar);

};

#endif