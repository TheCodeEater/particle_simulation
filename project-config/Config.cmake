####################
#
# Path definitions
# Define base paths for project folders
# Naming conventions: use program as the first word of the variable name
#
#####################

set(PROGRAM_SOURCES ${CMAKE_SOURCE_DIR}/src)
set(PROGRAM_HEADERS ${CMAKE_SOURCE_DIR}/include)

# Root config
# C++ std autodetection
set(CONFIG_AUTODETECT_ROOT_STD OFF)

# Libraries config
# Set wether needed libraries are shipped with the program or must be externally installed
# Default to off
# Currenlty has nos effect
set(CONFIG_LIBRARIES_INCLUDED OFF)