/*---------------------------------------------------------------------------*\
|* Title: SoundLibraryInterface.cpp                                           |
|* Date:  12 APRIL 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide interface for sound library to be called when    |
|                    compiled as a shared library.                            |
\*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/
#include "SoundLibraryInterface.h"
#include "Fluidsynth_class.h"
#include "InstrumentCollection.h"
#include "InstrumentBongos.h"
#include "InstrumentClave.h"
#include "InstrumentCowbell.h"

/*---------------------------------------------------------------------------*\
|*-------------------------------- GLOBALS ----------------------------------*|
\*---------------------------------------------------------------------------*/
CFluidSynth                     *g_pFluid                           = NULL;
CInstrumentCollection           *g_pCollection                      = NULL;
CInstrumentBase                 *g_pInstruments[NUM_INSTRUMENTS];

/*-----------------------------------------------------------------*\
|*------------------------ ConcatDirectory ------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Concatenate the specified path and directory strings.   |
|* Input:   path, directory                                         |
|* Output:  combined string                                         |
\*-----------------------------------------------------------------*/
void ConcatDirectory(char *buffer, const char *path, const char *directory)
{
    strcpy(buffer, path);
    strcat(buffer, directory);
}

/*-----------------------------------------------------------------*\
|*-------------------- InitializeSoundLibrary ---------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Initialize the SoundLibrary shared object.              |
|* Process: + Free any existing sound library instance              |
|*          + Initialize fluidsynth class                           |
|*          + Initialize instrument collection class                |
|*          + Initialize all individual instruments and load in     |
|*              sound fonts                                         |
|* Input:   Path to directory with sound fonts. Must be relative to |
|*          this shared object.                                     |
|* Output:  Returns zero on success, non-zero on failure            |
\*-----------------------------------------------------------------*/
int InitializeSoundLibrary(char *ipPathToSoundFonts)
{
    const char *soundFontFiles[NUM_INSTRUMENTS];
    char pathsToSoundFontFiles[NUM_INSTRUMENTS][255];

    /* duration of one bar in ticks. Must be divisible by 8! */
    double bpm = 100;//2.4E5 / bpm
    unsigned int duration = 2.4E5/bpm; // 2400 is 100bpm

    /* Free the library if it's been initialized before */
    FreeSoundLibrary();

    soundFontFiles[INSTRUMENT_BONGOS]        = "Congas Edition.sf2";
    soundFontFiles[INSTRUMENT_CLAVE]         = "claves.sf2";
    soundFontFiles[INSTRUMENT_COWBELL]       = "cowbell.sf2";

    g_pFluid = new CFluidSynth("SalsaMusicality");

    if ( g_pFluid->StartInit() != 0 ) {
        return 1;
    }

    /* Initialize volume */
    g_pFluid->SetMasterVolume(1.0);

    /* Initialize paths to sound font files  */
    for ( int i = 0; i < NUM_INSTRUMENTS; i++ ) {
        ConcatDirectory(
            pathsToSoundFontFiles[i],
            ipPathToSoundFonts,
            soundFontFiles[i]);
    }

    /* Initialize instrument collection */
    g_pCollection = new CInstrumentCollection(g_pFluid, duration);

    /* Initialize bongos */
    g_pInstruments[INSTRUMENT_BONGOS] =
        new CInstrumentBongos(pathsToSoundFontFiles[INSTRUMENT_BONGOS], true, 1);

    g_pCollection->AddInstrumentToCollection(g_pInstruments[INSTRUMENT_BONGOS]);

    /* Initialize clave */
    g_pInstruments[INSTRUMENT_CLAVE] =
        new CInstrumentClave(pathsToSoundFontFiles[INSTRUMENT_CLAVE], true, 1);

    g_pCollection->AddInstrumentToCollection(g_pInstruments[INSTRUMENT_CLAVE]);

    /* Initialize cowbell */
    g_pInstruments[INSTRUMENT_COWBELL] =
        new CInstrumentCowbell(pathsToSoundFontFiles[INSTRUMENT_COWBELL], true, 1);

    g_pCollection->AddInstrumentToCollection(g_pInstruments[INSTRUMENT_COWBELL]);

    if ( g_pFluid->FinishInit() != 0 ) {
        return 1;
    }

    return 0;
}

/*-----------------------------------------------------------------*\
|*----------------------- FreeSoundLibrary ------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Free all memory allocated by the SoundLibrary shared    |
|*          object.                                                 |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void FreeSoundLibrary(void)
{
    if ( g_pFluid ) {
        delete g_pFluid;
        g_pFluid = NULL;
    }

    if ( g_pCollection ) {
        delete g_pCollection;
        g_pCollection = NULL;
    }
}

/*-----------------------------------------------------------------*\
|*------------------------- BeginPlayback -------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Begin playback of all instruments.                      |
|* Input:   N/A                                                     |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void BeginPlayback(void)
{
    g_pFluid->BeginPlayback();
}

/*-----------------------------------------------------------------*\
|*----------------------- SetBeatsPerMinute -----------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the beats per minute to play the instruments at.    |
|* Input:   Beats per minute                                        |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetBeatsPerMinute(unsigned int iBpm)
{
    unsigned int duration = (unsigned int)(2.4E5/ iBpm); // 2400 is 100bpm
    g_pCollection->SetDurationOfOneBar(duration);
}

/*-----------------------------------------------------------------*\
|*--------------------- SetInstrumentEnabled ----------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the enabledness of the specified instrument.        |
|* Input:   Instrument index                                        |
|*          Is enabled boolean                                      |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetInstrumentEnabled(
    unsigned int                iInstrument,
    bool                        iIsEnabled )
{
    if ( ( iIsEnabled &&
           !g_pInstruments[iInstrument]->IsEnabled() ) ||
         ( !iIsEnabled &&
           g_pInstruments[iInstrument]->IsEnabled() ) )
    {
        g_pInstruments[iInstrument]->Toggle();
    }
}

/*-----------------------------------------------------------------*\
|*---------------------- IsInstrumentEnabled ----------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Determine if playback of the given instrument is        |
|*          enabled.                                                |
|* Input:   Instrument index                                        |
|* Output:  Is enabled boolean                                      |
\*-----------------------------------------------------------------*/
bool IsInstrumentEnabled(unsigned int iInstrument)
{
    return g_pInstruments[iInstrument]->IsEnabled();
}

/*-----------------------------------------------------------------*\
|*---------------------- SetInstrumentRhythm ----------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the rhythm for the specified instrument.            |
|* Input:   Instrument index, Rhythm index                          |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetInstrumentRhythm(
    unsigned int                iInstrument,
    short                           iRhythm )
{
    g_pInstruments[iInstrument]->SetRhythm(iRhythm);
}

/*-----------------------------------------------------------------*\
|*---------------------- SetClaveRhythm ---------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the rhythm for the specified instrument.            |
|* Input:   Instrument index, Rhythm index                          |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetClaveRhythm(
    short                           iRhythm )
{   
    int m_iBongoRhythm = g_pInstruments[INSTRUMENT_BONGOS]->GetRhythm();
    int m_iCowbellRhythm = g_pInstruments[INSTRUMENT_COWBELL]->GetRhythm();

    g_pInstruments[INSTRUMENT_CLAVE]->SetRhythm(iRhythm);
    
    if (m_iBongoRhythm%2!=iRhythm%2){
        if (m_iBongoRhythm%2==0){
            g_pInstruments[INSTRUMENT_BONGOS]->SetRhythm(m_iBongoRhythm-1);
        } 
        else if (m_iBongoRhythm%2==1){
            g_pInstruments[INSTRUMENT_BONGOS]->SetRhythm(m_iBongoRhythm+1);
        }
    }

    if (m_iCowbellRhythm%2!=iRhythm%2){
        if (m_iCowbellRhythm%2==0){
            g_pInstruments[INSTRUMENT_COWBELL]->SetRhythm(m_iCowbellRhythm-1);
        } 
        else if (m_iCowbellRhythm%2==1){
            g_pInstruments[INSTRUMENT_COWBELL]->SetRhythm(m_iCowbellRhythm+1);
        }
    }


}

/*-----------------------------------------------------------------*\
|*------------------------ SetMasterVolume ------------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the master volume for fluidsynth.                   |
|* Input:   Volume gain                                             |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetMasterVolume(float iVolume)
{
    g_pFluid->SetMasterVolume(iVolume);
}

/*-----------------------------------------------------------------*\
|*----------------------- SetInstrumentVolume ---------------------*|
|*-----------------------------------------------------------------*|
|* Purpose: Set the volume for the specified instrument.            |
|* Input:   Instrument index, Volume gain                           |
|* Output:  N/A                                                     |
\*-----------------------------------------------------------------*/
void SetInstrumentVolume(
    unsigned int                iInstrument,
    float                       iVolume )
{
    g_pInstruments[iInstrument]->SetVolume(iVolume);
}