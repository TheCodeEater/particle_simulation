# Program modules configuration
# Defines variables that hold source/header files to be compilated
# Variables must have this structure: PROGRAM_MODULES_<module_name>_<SRC/H>
# Main is the only exception
# Do not recall data from libraries.cmake, unless you edit the CMakelists.txt appropriately
# Note: use this only for program-specific code, if you plan to use shared components,
# add them as a library
include_guard(DIRECTORY)
 set(PROGRAM_MODULES_MAIN
         ${PROGRAM_SOURCES}/main.cpp
         ${PROGRAM_HEADERS}/Definitions.hpp)

#Example
# set(PROGRAM_MODULES_GRAPHICS_SRC ${PROGRAM_SOURCES}/graphics.cpp)
# set(PROGRAM_MDOULES_GRAPHICS_H ${PROGRAM_HEADERS}/graphics.hpp)
