using System;
using System.Runtime.InteropServices;
namespace SalsaMusicalityGUI
{
    internal enum INSTRUMENTS_TYPE
    {
        INSTRUMENT_CONGAS = 0,
        INSTRUMENT_CLAVE,
        INSTRUMENT_COWBELL,
        INSTRUMENT_BONGOS,
        NUM_INSTRUMENTS
    };

    internal enum BONGO_RHYTHMS_TYPE
    {
        BON_ALL_BEATS = 0,
        BON_MARTILLO,
        NUM_BONGO_RHYTHMS
    };

    internal enum CLAVE_RHYTHMS_TYPE
    {
        CLA_SON_2_3 = 0,
        CLA_SON_3_2,
        CLA_RUMBA_2_3,
        CLA_RUMBA_3_2,
        NUM_CLAVE_RHYTHMS
    };

    internal enum CONGA_RHYTHMS_TYPE
    {
        CON_BASIC_OFFBEAT = 0,
        CON_BASIC_ENDBEAT,
        CON_CLAVE_ALIGNED,
        NUM_CONGA_RHYTHMS
    };

    internal enum COWBELL_RHYTHMS_TYPE
    {
        COW_ALL_BEATS = 0,
        COW_DOWN_BEATS,
        COW_CLAVE_ALIGNED,
        NUM_COWBELL_RHYTHMS
    };

    internal static class SoundLibraryInterface
    {
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
        [DllImport("libSoundLibraries.so",
            CallingConvention=CallingConvention.Cdecl,
            CharSet = CharSet.Ansi,
            EntryPoint = "InitializeSoundLibrary")]
        internal static extern int InitializeSoundLibrary(
            [MarshalAs(UnmanagedType.LPStr)] string ipPathToSoundFonts);

        /*-----------------------------------------------------------------*\
        |*----------------------- FreeSoundLibrary ------------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Free all memory allocated by the SoundLibrary shared    |
        |*          object.                                                 |
        |* Input:   N/A                                                     |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "FreeSoundLibrary")]
        internal static extern void FreeSoundLibrary();

        /*-----------------------------------------------------------------*\
        |*------------------------- BeginPlayback -------------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Begin playback of all instruments.                      |
        |* Input:   N/A                                                     |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "BeginPlayback")]
        internal static extern void BeginPlayback();

        /*-----------------------------------------------------------------*\
        |*----------------------- SetBeatsPerMinute -----------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Set the beats per minute to play the instruments at.    |
        |* Input:   Beats per minute                                        |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "SetBeatsPerMinute")]
        internal static extern void SetBeatsPerMinute(uint iBpm);

        /*-----------------------------------------------------------------*\
        |*--------------------- SetInstrumentEnabled ----------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Set the enabledness of the specified instrument.        |
        |* Input:   Instrument index                                        |
        |*          Is enabled boolean                                      |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "SetInstrumentEnabled")]
        internal static extern void SetInstrumentEnabled(
            uint iInstrument,
            [MarshalAs(UnmanagedType.U1)] bool iIsEnabled);

        /*-----------------------------------------------------------------*\
        |*---------------------- IsInstrumentEnabled ----------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Determine if playback of the given instrument is        |
        |*          enabled.                                                |
        |* Input:   Instrument index                                        |
        |* Output:  Is enabled boolean                                      |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "IsInstrumentEnabled")]
        [return: MarshalAs(UnmanagedType.U1)]
        internal static extern bool IsInstrumentEnabled(uint iInstrument);

        /*-----------------------------------------------------------------*\
        |*---------------------- SetInstrumentRhythm ----------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Set the rhythm for the specified instrument.            |
        |* Input:   Instrument index, Rhythm index                          |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "SetInstrumentRhythm")]
        internal static extern void SetInstrumentRhythm(
            uint iInstrument,
            short iRhythm);

        /*-----------------------------------------------------------------*\
        |*---------------------- GetInstrumentRhythm ----------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Get the rhythm for the specified instrument.            |
        |* Input:   Instrument index                                        |
        |* Output:  Rhythm index                                            |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "GetInstrumentRhythm")]
        internal static extern short GetInstrumentRhythm(uint iInstrument);

        /*-----------------------------------------------------------------*\
        |*------------------------ SetMasterVolume ------------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Set the master volume for fluidsynth.                   |
        |* Input:   Volume gain                                             |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "SetMasterVolume")]
        internal static extern void SetMasterVolume(float iVolume);

        /*-----------------------------------------------------------------*\
        |*----------------------- SetInstrumentVolume ---------------------*|
        |*-----------------------------------------------------------------*|
        |* Purpose: Set the volume for the specified instrument.            |
        |* Input:   Instrument index, Volume gain                           |
        |* Output:  N/A                                                     |
        \*-----------------------------------------------------------------*/
        [DllImport("libSoundLibraries.so",
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "SetInstrumentVolume")]
        internal static extern void SetInstrumentVolume(
            uint iInstrument,
            float iVolume);
    }
}
