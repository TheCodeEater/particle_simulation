#
# Libraries config file
# This scripts finds dependencies and configures them

# Libraries path define
# Add path to local libraries
link_directories()

#find package section
find_package(ROOT REQUIRED)

#link libraries defines
#Define a set of libraries to be linked
#Variables must have this structure: PROGRAM_LIBRARIES_<combination_name>
set(PROGRAM_LIBRARIES_DEFAULT ROOT)
