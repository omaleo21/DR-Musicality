using System;
using System.Runtime.InteropServices;
namespace SalsaMusicalityGUI
{
    internal enum INSTRUMENTS_TYPE
    {
        INSTRUMENT_BONGOS = 0,
        INSTRUMENT_CLAVE,
        INSTRUMENT_COWBELL,
        NUM_INSTRUMENTS
    };

    internal enum RHYTHMS_TYPE
    {
        DEFAULT,
        NUM_RHYTHMS_TYPE
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
            uint iRhythm);

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
