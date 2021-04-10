/*---------------------------------------------------------------------------*\
|* Title: InstrumentBase.h
|* Date:  30 MARCH 2021
|*
|*-----------------------------------------------------------------------------
|* File Description: Provide abstract class for playing notes using an instrument
|*
\*---------------------------------------------------------------------------*/
#ifndef INSTRUMENT_BASE_H
#define INSTRUMENT_BASE_H

/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include <string.h>

/*---------------------------------------------------------------------------*\
|*--------------------- NOTE LINKED LIST STRUCTURE --------------------------*|
\*---------------------------------------------------------------------------*/
struct Note
{
    int                 m_iChannel;
    short               m_iKey;
    unsigned int        m_iNoteOnTime;
    unsigned int        m_iNoteOffTime;

    Note                *pNext;
    Note                *pPrev;

    /*-----------------------------------------------------------------*\
    |*------------------------ Note::Note() ---------------------------*|
    |*-----------------------------------------------------------------*|
    |* Purpose: Initialize member variables to default values.          |
    |* Input:   N/A                                                     |   
    |* Output:  N/A                                                     |
    \*-----------------------------------------------------------------*/
    Note()
    {
        m_iChannel          = -1;
        m_iKey              = -1;
        m_iNoteOnTime       = -1;
        m_iNoteOffTime      = -1;

        pNext               = NULL;
        pPrev               = NULL;
    }

    /*-----------------------------------------------------------------*\
    |*------------------- Note::CreateLinkedList ----------------------*|
    |*-----------------------------------------------------------------*|
    |* Purpose: Create a linked list of notes, size "iSize".            |
    |* Input:   Size of list                                            |
    |* Output:  N/A                                                     |
    \*-----------------------------------------------------------------*/
    static Note *CreateLinkedList(const int iSize)
    {
        Note *pFirstNote = NULL;
        Note *pPrev = NULL;

        for ( int i = 0; i < iSize; i++ ) {
            Note *pNewNote = new Note;

            if ( pPrev ) {
                pPrev->pNext = pNewNote;
            } else {
                pFirstNote = pNewNote; // Set notes member variable to first note
            }

            pNewNote->pPrev = pPrev;
            pPrev = pNewNote;
        }

        pPrev->pNext = NULL;

        return pFirstNote;
    }

    /*-----------------------------------------------------------------*\
    |*--------------------- Note::FreeLinkedList ----------------------*|
    |*-----------------------------------------------------------------*|
    |* Purpose: Free the memory associated with the nodes of the        |
    |*          specified list.                                         |
    |* Input:   First note of linked list                               |
    |* Output:  N/A                                                     |
    \*-----------------------------------------------------------------*/
    static void FreeLinkedList(Note *pHead)
    {
        Note *pLast = pHead;

        while ( pLast->pNext ) {
            pLast = pLast->pNext;
        }

        while ( pLast->pPrev ) {
            pLast = pLast->pPrev;
            delete pLast->pNext;
            pLast->pNext = NULL;
        }
    }
};

/*---------------------------------------------------------------------------*\
|*------------------------ BASE INSTRUMENT CLASS ----------------------------*|
\*---------------------------------------------------------------------------*/
class CInstrumentBase
{
public:
    CInstrumentBase(
        const char                  *ipPathToSoundFont,
        const bool                  &iIsEnabled,
        const short                 &iKeyFactor );

    virtual ~CInstrumentBase();

    virtual Note *GetNotes(
        const unsigned int          &iTimeOfNextPattern,
        const int                   &iDuration,
        const int                   iBeatTimes[8] );

    virtual void SetChannel(const int &iChannel) { m_iChannel = iChannel; }

    virtual void Toggle() { m_bIsEnabled = !m_bIsEnabled; }

    virtual bool IsEnabled() { return m_bIsEnabled; }

    virtual const char *GetPathToSoundFont(void) { return m_pPathToSoundFont; }

protected:
    const char                  *m_pPathToSoundFont;
    bool                        m_bIsEnabled;
    int                         m_iChannel;
    short                       m_iKeyFactor;
    Note                        *m_pNotes;

};

#endif