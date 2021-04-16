/*---------------------------------------------------------------------------*\
|* Title: SoundLibraryInterface.h                                             |
|* Date:  30 MARCH 2021                                                       |
|*                                                                            |
|*----------------------------------------------------------------------------|
|* File Description: Provide interface for sound library to be called when    |
|                    compiled as a shared library.                            |
\*---------------------------------------------------------------------------*/
#ifndef SOUND_LIBRARY_INTERFACE_H
#define SOUND_LIBRARY_INTERFACE_H

/*---------------------------------------------------------------------------*\
|*------------------------------- ENUMERATIONS ------------------------------*|
\*---------------------------------------------------------------------------*/
enum INSTRUMENTS_TYPE {
    INSTRUMENT_BONGOS = 0,
    INSTRUMENT_CLAVE,
    INSTRUMENT_COWBELL,
    NUM_INSTRUMENTS
};

enum RHYTHMS_TYPE {
    DEFAULT,
    NUM_RHYTHMS_TYPE
};

/*---------------------------------------------------------------------------*\
|*--------------------------------- EXPORTS ---------------------------------*|
\*---------------------------------------------------------------------------*/
#ifdef WIN32
#define SLAPI_EXPORT extern "C" __declspec(dllexport)
#else
#define SLAPI_EXPORT extern "C"
#endif

SLAPI_EXPORT int InitializeSoundLibrary(char *ipPathToSoundFonts);
SLAPI_EXPORT void FreeSoundLibrary(void);

SLAPI_EXPORT void BeginPlayback(void);

SLAPI_EXPORT void SetBeatsPerMinute(unsigned int iBpm);

SLAPI_EXPORT void SetInstrumentEnabled(
    unsigned int                iInstrument,
    bool                        iIsEnabled );

SLAPI_EXPORT bool IsInstrumentEnabled(unsigned int iInstrument);

SLAPI_EXPORT void SetInstrumentRhythm(
    unsigned int                iInstrument,
    short                       iRhythm );

SLAPI_EXPORT void SetClaveRhythm(
    short                       iRhythm );

SLAPI_EXPORT void SetMasterVolume(float iVolume);

SLAPI_EXPORT void SetInstrumentVolume(
    unsigned int                iInstrument,
    float                       iVolume );


#endif