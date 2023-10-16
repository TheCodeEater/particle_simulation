####################
#
# Path definitions
# Define base paths for project folders
# Naming conventions: use program as the first word of the variable name
#
#####################
include_guard(DIRECTORY)

set(PROGRAM_SOURCES ${CMAKE_SOURCE_DIR}/main/src)
set(PROGRAM_HEADERS ${CMAKE_SOURCE_DIR}/main/include)
set(PROGRAM_COMPONENTS ${CMAKE_SOURCE_DIR}/components)
set(PROGRAM_CODE_TEMPLATES ${CMAKE_SOURCE_DIR}/templates)

###########
# Code metadata definitions
#Define variables to configure template code files
###########
set(PROGRAM_NAMESPACE RootApplication)
set(PROGRAM_NAME "RootTemplate")
set(PROGRAM_ATTACH_CLING TRUE)

# Root config
# C++ std autodetection
set(CONFIG_AUTODETECT_ROOT_STD OFF)
