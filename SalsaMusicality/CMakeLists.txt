# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Name our project; State the languages in use and the current version
project ("SalsaMusicality")

# State the language in use

enable_language(CXX)

# Set the c++ standard to build with. C++99 should be compatible with multiple platforms
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Turn on warning checks
if (MSVC)
    add_compile_options (/W4)
else (MSVC)
    add_compile_options (-Wall -Wextra -fpermissive)
endif (MSVC)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")

# Set option for using pkg-config to locate dependencies
option ( enable-pkgconfig "use pkg-config to locate dependencies" on )

# Set option for Darwinism
if ( CMAKE_SYSTEM MATCHES "Darwin" )
    option ( enable-framework "create a Mac OSX style ${PROJECT_NAME}.framework" on )
endif ( CMAKE_SYSTEM MATCHES "Darwin" )

# Set local var for where fluidsynth is stored
set (FLUIDSYNTH_DIR "${CMAKE_SOURCE_DIR}/../fluidsynth")

# Set local var for path to fluidsynth library file
if ( MSVC ) 
    set (FLUIDSYNTH_LIB "${FLUIDSYNTH_DIR}/out/build/x64-Debug/src/fluidsynth.lib")
elseif ( enable-framework )
    set (FLUIDSYNTH_LIB "${FLUIDSYNTH_DIR}/src/FluidSynth.framework/FluidSynth")
else ( MSVC )
    set (FLUIDSYNTH_LIB "${FLUIDSYNTH_DIR}/src/libfluidsynth.so")
endif ( MSVC )

# Find glib2 include and library paths
if(NOT enable-pkgconfig)

    FIND_LIBRARY( GLIB_LIB NAMES glib glib-2.0 PATH GLIB_LIBRARY_DIR )
    #FIND_LIBRARY( GTHREAD_LIB NAMES gthread gthread-2.0 PATH GTHREAD_LIBRARY_DIR )
    FIND_PATH( GLIBH_DIR glib.h PATH GLIB_INCLUDE_DIR )
    #FIND_PATH( GLIBCONF_DIR glibconfig.h PATH GLIBCONF_INCLUDE_DIR )

    IF( GLIB_LIB MATCHES "GLIB_LIB-NOTFOUND" OR
           # GTHREAD_LIB MATCHES "GTHREAD_LIB-NOTFOUND" OR
            GLIBH_DIR MATCHES "GLIBH_DIR-NOTFOUND" ) #OR
            #GLIBCONF_DIR MATCHES "GLIBCONF_DIR-NOTFOUND")
            message( WARNING "Not sure if I found GLIB, continuing anyway.")
    ENDIF()

    SET( GLIB_INCLUDE_DIRS ${GLIBH_DIR} )
    #SET( GLIB_LIBRARIES ${GLIB_LIB} ${GTHREAD_LIB} )

    message( STATUS "GLIB_INCLUDE_DIRS: " ${GLIB_INCLUDE_DIRS} )
    message( STATUS "GLIB_LIBRARIES: " ${GLIB_LIBRARIES} )

else(NOT enable-pkgconfig)

    find_package ( PkgConfig REQUIRED )

    # Mandatory libraries: glib and gthread
    pkg_check_modules ( GLIB REQUIRED glib-2.0>=2.6.5 gthread-2.0>=2.6.5 )

    if ( GLIB_glib-2.0_VERSION AND GLIB_glib-2.0_VERSION VERSION_LESS "2.26.0" )
        message ( WARNING "Your version of glib is very old. This may cause problems with fluidsynth's sample cache on Windows. Consider updating to glib 2.26 or newer!" )
    endif ( GLIB_glib-2.0_VERSION AND GLIB_glib-2.0_VERSION VERSION_LESS "2.26.0" )

endif(NOT enable-pkgconfig)

# Find SDL2 include and library paths
find_package(SDL2 REQUIRED)

# Set up include directories required for this project
include_directories(PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${FLUIDSYNTH_DIR}
    "${FLUIDSYNTH_DIR}/include"
    "${FLUIDSYNTH_DIR}/src"
    "${FLUIDSYNTH_DIR}/src/utils"
    "${FLUIDSYNTH_DIR}/src/sfloader"
    "${FLUIDSYNTH_DIR}/src/rvoice"
    "${FLUIDSYNTH_DIR}/src/midi"
    "${FLUIDSYNTH_DIR}/src/bindings" )

# List source files to compile
set(SOURCES
        SoundLibraries/Fluidsynth_class.cpp
        SoundLibraries/InstrumentBase.cpp
        SoundLibraries/SheetMusic.cpp
        SoundLibraries/InstrumentBongos.cpp
        SoundLibraries/InstrumentClave.cpp
        SoundLibraries/InstrumentCowbell.cpp
        SoundLibraries/InstrumentCollection.cpp )
        

# Compile sources into object library
add_library( ${PROJECT_NAME}-OBJ OBJECT ${SOURCES})

# Link the project
target_link_libraries( ${PROJECT_NAME} ${FLUIDSYNTH_LIB} ${SDL2_LIBRARIES} ${PROJECT_NAME}-OBJ )


