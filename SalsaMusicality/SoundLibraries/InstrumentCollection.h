/*---------------------------------------------------------------------------*\
|* Title: InstrumentCollection.h
|* Date:  6 APRIL 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing a collection of instruments with
|*                   the CFluidSynth class.
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_COLLECTION_H
#define INSTRUMENT_COLLECTION_H

/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include <vector>

/*---------------------------------------------------------------------------*\
|*------------------------------ LOCAL INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include "Fluidsynth_class.h"
#include "InstrumentBase.h"

class CInstrumentCollection
{
public:
    CInstrumentCollection(
        CFluidSynth                     *ipFluid,
        const unsigned int              &iDurationOfOneBar );

    virtual ~CInstrumentCollection();

    virtual int AddInstrumentToCollection(CInstrumentBase *ipInstrument);

private:
    static void SchedulePattern(
        void                            *pData,
        unsigned int                    &ioStartTimeOfNextPattern );

    CFluidSynth                         *m_pFluid;

    std::vector<CInstrumentBase *>      *m_vInstruments;

    unsigned int                        m_iDurationOfOneBar;
    unsigned int                        m_iDurationOfHalfBeat;
};


#endif