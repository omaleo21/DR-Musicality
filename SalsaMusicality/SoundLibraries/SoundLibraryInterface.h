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
    INSTRUMENT_CONGAS = 0,
    INSTRUMENT_CLAVE,
    INSTRUMENT_COWBELL,
    INSTRUMENT_BONGOS,
    NUM_INSTRUMENTS
};

enum RHYTHMS_TYPE {
    DEFAULT,
    NUM_RHYTHMS_TYPE
};

enum BONGO_RHYTHMS {
    ALL_BEATS = 0,
    MARTILLO,
    NUM_BONGO_RHYTHMS
};

enum CLAVE_RHYTHMS {
    SON_2_3 = 0,
    SON_3_2,
    RUMBA_2_3,
    RUMBA_3_2,
    NUM_CLAVE_RHYTHMS
};

enum CONGA_RHYTHMS {
    BASIC_OFFBEAT = 0,
    BASIC_ENDBEAT,
    CLAVE_ALIGNED,
    NUM_CONGA_RHYTHMS
};
/*
enum COWBELL_RHYTHMS {
    ALL_BEATS = 0,
    DOWN_BEATS,
    CLAVE_ALIGNED,
    NUM_COWBELL_RHYTHMS
};
*/
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