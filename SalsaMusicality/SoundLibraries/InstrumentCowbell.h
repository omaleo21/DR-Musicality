/*---------------------------------------------------------------------------*\
|* Title: InstrumentCowbell.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing cowbell notes.
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_COWBELL_H
#define INSTRUMENT_COWBELL_H

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBase.h"
#include "SheetMusic.h"

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentCowbell : public virtual CInstrumentBase
{
public:
    CInstrumentCowbell(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iRhythm );

    virtual ~CInstrumentCowbell() {};

    virtual Note *GetNotes(
        const int                   iBeatTimes[8],
        const SharedInstrumentData  *ipSharedData );

private:
    bool m_bFirstBar;

    Note_structure N;

    Note_structure All_Beats(Note_structure N, const int iBeatTimes[8]);

    Note_structure Down_Beats(Note_structure N, const int iBeatTimes[8]);

    Note_structure Advanced_Asym(Note_structure N, const int iBeatTimes[8],bool m_bFirstBar);
};

#endif