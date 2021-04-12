/*---------------------------------------------------------------------------*\
|*----------------------------- SYSTEM INCLUDES -----------------------------*|
\*---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------*\
|*----------------------------- LOCAL INCLUDES ------------------------------*|
\*---------------------------------------------------------------------------*/
#include "SoundLibraries/Fluidsynth_class.h"
#include "SoundLibraries/InstrumentBongos.h"
#include "SoundLibraries/InstrumentClave.h"
#include "SoundLibraries/InstrumentCowbell.h"
#include "SoundLibraries/InstrumentCollection.h"

/*---------------------------------------------------------------------------*\
|*--------------------------- PATH FOR SOUNDFONTS ---------------------------*|
\*---------------------------------------------------------------------------*/

const char *SoundFontsPath = "./SoundFonts/";

/*---------------------------------------------------------------------------*\
|*-------------------------------- FUNCTIONS --------------------------------*|
\*---------------------------------------------------------------------------*/
/* concatenate sound font file at the end of path */
void concat_directory(char *buffer, const char *path, const char *directory)
{
    strcpy(buffer, path);
    strcat(buffer, directory);
}


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
    CFluidSynth *pFluid                         = NULL;
    CInstrumentCollection *pCollection          = NULL;
    CInstrumentBongos *pBongos                  = NULL;
    CInstrumentClave *pClave                    = NULL;
    CInstrumentCowbell *pCowbell                = NULL;

    /* duration of the pattern in ticks. Must be divisible by 8! */
    double bpm = 100;//2.4E5 / bpm
    unsigned int duration = 2.4E5/bpm; // 2400 is 100bpm

    //double bpm = 4.8E5 / duration;
    char pathToBongo[100];
    char pathToClave[100];
    char pathToCowbell[100];

    int n = -1, n2 = -1, n3 = -1;

    pFluid = new CFluidSynth("SalsaMusicality");

    if ( argc == 2 && !strcmp(argv[1], "-h") ) {
        usage("FluidSynthTesting");
        return 0;
    }

    if ( pFluid->StartInit() != 0 ) {
        return 1;
    }

    pFluid->SetMasterVolume(1.0);

    /* load the SoundFonts */

    concat_directory(pathToBongo, SoundFontsPath, "Congas Edition.sf2");
    concat_directory(pathToClave, SoundFontsPath, "claves.sf2");
    concat_directory(pathToCowbell, SoundFontsPath, "cowbell.sf2");

    pCollection = new CInstrumentCollection(pFluid, duration);

    pBongos = new CInstrumentBongos(pathToBongo, true, 1);
    n = pCollection->AddInstrumentToCollection(pBongos);

    pClave = new CInstrumentClave(pathToClave, false, 1);
    n2 = pCollection->AddInstrumentToCollection(pClave);

    pCowbell = new CInstrumentCowbell(pathToCowbell, true, 1);
    n3 = pCollection->AddInstrumentToCollection(pCowbell);

    if(n != -1 && n2 != -1 && n3 != -1)
    {
        if ( pFluid->FinishInit() != 0 ) {
            return 1;
        }

        /* schedule patterns */
        pFluid->BeginPlayback();

        /* wait for user input */
        printf("press <q> then <enter> to stop\n");
        while ( n != 'q' ) {
            n = getchar();

            if ( n == 'b' ) {
                pBongos->Toggle();
            }
            if ( n == 'c' ) {
                pClave->Toggle();
            }
            if ( n == 'w' ) {
                pCowbell->Toggle();
            }
        }

    }

    /* clean and exit */
    
    delete pFluid;

    return 0;
}
