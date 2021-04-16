/*---------------------------------------------------------------------------*\
|* Title: InstrumentClave.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing clave notes.
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_CLAVE_H
#define INSTRUMENT_CLAVE_H

/*---------------------------------------------------------------------------*\
|*---------------------------- LOCAL INCLUDES -------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBase.h"
#include "SheetMusic.h"

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentClave : public virtual CInstrumentBase
{
public:
    CInstrumentClave(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iRhythm );

    virtual ~CInstrumentClave() {};

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

private:
    bool m_bFirstBar;

};

#endif