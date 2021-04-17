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
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentBongos : public virtual CInstrumentBase
{
public:
    CInstrumentBongos(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iRhythm );

    virtual ~CInstrumentBongos() {};

    virtual Note *GetNotes(
        const int                   iBeatTimes[8],
        const SharedInstrumentData  *ipSharedData );

private:
    bool m_bFirstBar;

    Note_structure N;

    Note_structure All_Beats(Note_structure N, const int iBeatTimes[8]);
};

#endif