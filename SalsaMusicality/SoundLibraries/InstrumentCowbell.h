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
        const short                 &iKeyFactor );

    virtual ~CInstrumentCowbell() {};

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

private:
    bool m_bFirstBar;

};

#endif