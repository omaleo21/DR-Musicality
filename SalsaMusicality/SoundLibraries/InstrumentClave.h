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
        const int                   iBeatTimes[8],
        const SharedInstrumentData  *ipSharedData );

    virtual void UpdateSharedData(
        const int                   iBeatTimes[8],
        SharedInstrumentData        *iopSharedData );

private:
    bool m_bFirstBar;

    Note_structure N;

    Note_structure Son(Note_structure N, const int iBeatTimes[8]);

    Note_structure Rumba(Note_structure N, const int iBeatTimes[8]);

};

#endif