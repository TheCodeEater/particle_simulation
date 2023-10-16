####################
#
# Path definitions
# Define base paths for project folders
# Naming conventions: use program as the first word of the variable name
#
#####################

set(PROGRAM_SOURCES ${CMAKE_SOURCE_DIR}/main/src)
set(PROGRAM_HEADERS ${CMAKE_SOURCE_DIR}/main/include)
set(PROGRAM_COMPONENTS ${CMAKE_SOURCE_DIR}/components)

# Root config
# C++ std autodetection
set(CONFIG_AUTODETECT_ROOT_STD OFF)
