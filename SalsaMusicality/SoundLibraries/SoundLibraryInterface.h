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

enum BONGO_RHYTHMS {
    BON_ALL_BEATS = 0,
    BON_MARTILLO,
    NUM_BONGO_RHYTHMS
};

enum CLAVE_RHYTHMS {
    CLA_SON_2_3 = 0,
    CLA_SON_3_2,
    CLA_RUMBA_2_3,
    CLA_RUMBA_3_2,
    NUM_CLAVE_RHYTHMS
};

enum CONGA_RHYTHMS {
    CON_BASIC_OFFBEAT = 0,
    CON_BASIC_ENDBEAT,
    CON_CLAVE_ALIGNED,
    NUM_CONGA_RHYTHMS
};

enum COWBELL_RHYTHMS {
    COW_ALL_BEATS = 0,
    COW_DOWN_BEATS,
    COW_CLAVE_ALIGNED,
    NUM_COWBELL_RHYTHMS
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

SLAPI_EXPORT short GetInstrumentRhythm(unsigned int iInstrument);

SLAPI_EXPORT void SetMasterVolume(float iVolume);

SLAPI_EXPORT void SetInstrumentVolume(
    unsigned int                iInstrument,
    float                       iVolume );


#endif