# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

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

add_subdirectory(SoundLibraries)

# Link the project
target_link_libraries( ${PROJECT_NAME} SoundLibraries )
