# Program modules configuration
# Defines variables that hold source/header files to be compilated
# Variables must have this structure: PROGRAM_MODULES_<module_name>
# Do not recall data from libraries.cmake, unless you edit the CMakelists.txt appropriately
# Note: use this only for program-specific code, if you plan to use shared components,
# add them as a library
 set(PROGRAM_MODULES_MAIN ${PROGRAM_SOURCES}/main.cpp)