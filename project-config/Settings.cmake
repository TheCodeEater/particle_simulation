####################
#
# Path definitions
# Define base paths for project folders
# Naming conventions: use program as the first word of the variable name
#
#####################
include_guard(DIRECTORY)

set(PROGRAM_BASE ${CMAKE_SOURCE_DIR}/main)
set(PROGRAM_SOURCES ${PROGRAM_BASE}/src)
set(PROGRAM_HEADERS ${PROGRAM_BASE}/include)
set(PROGRAM_COMPONENTS ${CMAKE_SOURCE_DIR}/components)
set(PROGRAM_CODE_TEMPLATES ${CMAKE_SOURCE_DIR}/templates)
set(PROGRAM_TEST ${CMAKE_SOURCE_DIR}/tests)
set(PROGRAM_TEST_UNIT ${PROGRAM_TEST}/unit)

###########
# Code metadata definitions
#Define variables to configure template code files
###########
set(PROGRAM_NAMESPACE RootApplication)
set(PROGRAM_NAME "RootTemplate")
set(PROGRAM_ATTACH_CLING TRUE)
set(PROGRAM_USE_LOCAL_OWNERSHIP TRUE)

# Root config
# C++ std autodetection
set(CONFIG_AUTODETECT_ROOT_STD OFF)
