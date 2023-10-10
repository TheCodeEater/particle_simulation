#
# Libraries config file
# This scripts finds dependencies and configures them

# Libraries path define
# Add path to local libraries
# Note: the Find<library>.cmake must be placed in an immediate subdirectory of the specific
#library folder
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libraries)

#find package section
find_package(ROOT REQUIRED)

#link libraries defines
#Define a set of libraries to be linked
#Variables must have this structure: PROGRAM_LIBRARIES_<combination_name>
set(PROGRAM_LIBRARIES_DEFAULT ROOT::Core)
