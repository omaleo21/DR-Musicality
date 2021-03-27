# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth;/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/local/Cellar/cmake/3.19.7/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "FluidSynth built using CMake")
set(CPACK_GENERATOR "STGZ;TGZ;TBZ2;ZIP")
set(CPACK_INSTALL_CMAKE_PROJECTS "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth;FluidSynth;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/cmake_admin")
set(CPACK_NSIS_DISPLAY_NAME "fluidsynth 2.1.8")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "fluidsynth 2.1.8")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.1.sdk")
set(CPACK_OUTPUT_CONFIG_FILE "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "FluidSynth real-time synthesizer")
set(CPACK_PACKAGE_EXECUTABLES "fluidsynth;FluidSynth CLI")
set(CPACK_PACKAGE_FILE_NAME "fluidsynth-2.1.8-Darwin")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "fluidsynth 2.1.8")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "fluidsynth 2.1.8")
set(CPACK_PACKAGE_NAME "fluidsynth")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "fluidsynth.org")
set(CPACK_PACKAGE_VERSION "2.1.8")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "8")
set(CPACK_RESOURCE_FILE_LICENSE "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/LICENSE")
set(CPACK_RESOURCE_FILE_README "/usr/local/Cellar/cmake/3.19.7/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/local/Cellar/cmake/3.19.7/share/cmake/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ;TBZ2;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/.svn/;/build/;~$;.cproject;.project;/.settings/;")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "fluidsynth-2.1.8")
set(CPACK_SOURCE_STRIP_FILES "OFF")
set(CPACK_STRIP_FILES "ON")
set(CPACK_SYSTEM_NAME "Darwin")
set(CPACK_TOPLEVEL_TAG "Darwin")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/Users/omarleon/Documents/GitHub/DR-Musicality/fluidsynth/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
