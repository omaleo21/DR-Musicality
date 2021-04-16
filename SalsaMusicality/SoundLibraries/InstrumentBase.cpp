/*---------------------------------------------------------------------------*\
|* Title: InstrumentBase.cpp                                                  |
|* Date:  30 MARCH 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide abstract class for playing notes using an        |
|* instrument.                                                                |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*---------------------------- SYSTEM INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/
#include <string.h>

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/
#include "InstrumentBase.h"

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
CInstrumentBase::CInstrumentBase(
    const char                  *ipPathToSoundFont,
    const bool                  &iIsEnabled,
    const short                 &iKeyFactor )
    : m_pPathToSoundFont(ipPathToSoundFont),
      m_bIsEnabled(iIsEnabled),
      m_iChannel(-1),
      m_iKeyFactor(iKeyFactor),
      m_fVolume(1.0),
      m_pNotes(NULL)
{
}

CInstrumentBase::~CInstrumentBase()
{
    if (m_pNotes) {
        Note::FreeLinkedList(m_pNotes);
        delete m_pNotes;
        m_pNotes = NULL;
    }
}

Note *CInstrumentBase::GetNotes(
    const unsigned int          &iTimeOfNextPattern,
    const int                   &iDuration,
    const int                   iBeatTimes[8] )
{
    return m_pNotes;
}

void CInstrumentBase::SetVolume(const float &iVolume)
{
    m_fVolume = 0.1f * iVolume;

    if ( m_fVolume > 1.0f ) {
        m_fVolume = 1.0;
    } else if ( m_fVolume < 0.0 ) {
        m_fVolume = 0.0;
    }
}

void CInstrumentBase::SetRhythm(short &iRhythm)
{
    m_iKeyFactor = iRhythm;
}