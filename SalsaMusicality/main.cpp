/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/
#include "SoundLibraries/SoundLibraryInterface.h"

/*---------------------------------------------------------------------------*\
|*--------------------------- PATH FOR SOUNDFONTS ---------------------------*|
\*---------------------------------------------------------------------------*/
char *SoundFontsPath = "../SoundFonts/"; // Must be relative to SoundLibrary shared object

/*---------------------------------------------------------------------------*\
|*-------------------------------- FUNCTIONS --------------------------------*|
\*---------------------------------------------------------------------------*/
void usage(const char *prog_name)
{
    printf("Usage: %s\n", prog_name);
    printf("\tPress 'c' then enter to toggle the clave.\n");
    printf("\tPress 'w' then enter to toggle the cowbell.\n");
    printf("\tPress 'b' then enter to toggle the bongos.\n");
}

/*---------------------------------------------------------------------------*\
|*-------------------------------- PROGRAM MAIN -----------------------------*|
\*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    /* Local variables */
    int n = 0;
    bool isEnabled = false;

    /* duration of the pattern in ticks. Must be divisible by 8! */
    double bpm = 100;//2.4E5 / bpm
    unsigned int duration = 2.4E5/bpm; // 2400 is 100bpm

    if( !InitializeSoundLibrary(SoundFontsPath) )
    {
        /* schedule patterns */
        BeginPlayback();

        /* wait for user input */
        printf("press <q> then <enter> to stop\n");
        while ( n != 'q' ) {
            n = getchar();

            if ( n == 'b' ) {
                isEnabled = IsInstrumentEnabled(INSTRUMENT_BONGOS);
                SetInstrumentEnabled(INSTRUMENT_BONGOS, !isEnabled );
            }
            if ( n == 'c' ) {
                isEnabled = IsInstrumentEnabled(INSTRUMENT_CLAVE);
                SetInstrumentEnabled(INSTRUMENT_CLAVE, !isEnabled );
            }
            if ( n == 'w' ) {
                isEnabled = IsInstrumentEnabled(INSTRUMENT_COWBELL);
                SetInstrumentEnabled(INSTRUMENT_COWBELL, !isEnabled );
            }
        }

    }

    /* clean and exit */
    FreeSoundLibrary();

    return 0;
}
