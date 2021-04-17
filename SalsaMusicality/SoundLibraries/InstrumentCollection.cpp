/*---------------------------------------------------------------------------*\
|* Title: InstrumentCollection.cpp
|* Date:  6 APRIL 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide class for playing a collection of instruments with
|*                   the CFluidSynth class.
|*
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*------------------------------ LOCAL INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentCollection.h"

CInstrumentCollection::CInstrumentCollection(
    CFluidSynth                 *ipFluid,
    const unsigned int          &iDurationOfOneBar )
{
    m_pFluid = ipFluid;

    m_pFluid->SetCallbackFunction(&SchedulePattern, (void *)this);

    m_vInstruments = new std::vector<CInstrumentBase *>();

    m_pSharedData = new SharedInstrumentData();

    SetDurationOfOneBar(iDurationOfOneBar);
}

CInstrumentCollection::~CInstrumentCollection()
{
    if ( m_vInstruments ) {
        for ( int i = m_vInstruments->size() - 1; i >= 0; i-- ) {
            if ( m_vInstruments->at(i) ) {
                delete m_vInstruments->at(i);
            }
        }
        delete m_vInstruments;
        m_vInstruments = NULL;
    }

    if ( m_pSharedData ) {
        delete m_pSharedData;
        m_pSharedData = NULL;
    }
}

int CInstrumentCollection::AddInstrumentToCollection(CInstrumentBase *ipInstrument)
{
    int channel = -1;

    // First check that the instrument hasn't already been added
    for ( unsigned int i = 0; i < m_vInstruments->size(); i++ ) {
        if ( m_vInstruments->at(i) == ipInstrument ) {
            return -1;
        }
    }

    channel = m_pFluid->RegisterInstrument(ipInstrument->GetPathToSoundFont());

    if ( channel != -1 ) {
        ipInstrument->SetChannel(channel);
        m_vInstruments->push_back(ipInstrument);
    }

    return channel;
}

void CInstrumentCollection::SchedulePattern(
    void                *pData,
    unsigned int        &ioStartTimeOfNextPattern )
{
    CInstrumentCollection *pCollection = (CInstrumentCollection *)pData;
    int beatTimes[8];
    unsigned int i = 0;

    beatTimes[0] = ioStartTimeOfNextPattern;

    for ( i = 1; i < 8; i++) {
        beatTimes[i] = beatTimes[i - 1] + pCollection->m_iDurationOfHalfBeat;
    }

    /* Update the shared data object before calling GetNotes() */
    for ( i = 0; i < pCollection->m_vInstruments->size(); i++ ) {
        CInstrumentBase *pInstrument = pCollection->m_vInstruments->at(i);

        pInstrument->UpdateSharedData(
            beatTimes,
            pCollection->m_pSharedData );
    }

    for ( i = 0; i < pCollection->m_vInstruments->size(); i++ ) {
        CInstrumentBase *pInstrument = pCollection->m_vInstruments->at(i);

        Note *pNotes =
            pInstrument->GetNotes(
                beatTimes,
                pCollection->m_pSharedData );

        if ( pInstrument->IsEnabled() ) {

            /* Channel = -1 indicates we're done playing notes */
            while ( pNotes && pNotes->m_iChannel != -1 ) {
                
                pCollection->m_pFluid->ScheduleNoteOn(
                    pNotes->m_iChannel,
                    pNotes->m_iKey,
                    (short)(pInstrument->GetVolume() * pNotes->m_iVelocity),
                    pNotes->m_iNoteOnTime );

                pCollection->m_pFluid->ScheduleNoteOff(
                    pNotes->m_iChannel,
                    pNotes->m_iKey,
                    pNotes->m_iNoteOffTime );

                pNotes = pNotes->pNext;
            }
        }
    }

    ioStartTimeOfNextPattern += pCollection->m_iDurationOfOneBar;
}

void CInstrumentCollection::SetDurationOfOneBar(const unsigned int &iDurationOfOneBar)
{
    m_iDurationOfOneBar = iDurationOfOneBar;

    /* Ensure that the duration is a multiple of 8 */
    int rem = m_iDurationOfOneBar % 8;
    if ( rem != 0 ) {
        m_iDurationOfOneBar += 8 - rem;
    }

    // Calculate length of one-half beat (time between 1& and 2)
    m_iDurationOfHalfBeat = m_iDurationOfOneBar / 8;
}