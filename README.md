# DR-Musicality

# On MAC

1) Download SDL2 driver
    Download zip from https://www.libsdl.org/download-2.0.php
    After unzipping it and then navigating to that directory
    ./configure
    make
    make install

2) Go to fluidsynth folder
    cmake CMakeList.txt
    make

3) Go to main folder
    Ensure that set (FLUIDSYNTH_LIB "${FLUIDSYNTH_DIR}/src/FluidSynth.framework/FluidSynth") exists.
    cmake CMakeList.txt
    make

4) Execute using ./SalsaMusicality