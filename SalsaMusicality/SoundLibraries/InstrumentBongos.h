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
        const short                 &iKeyFactor );

    virtual ~CInstrumentBongos() {};

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

private:
    bool m_bFirstBar;
};

#endif