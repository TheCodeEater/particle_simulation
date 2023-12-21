#
# Libraries config file
# This scripts finds dependencies and configures them
include_guard(DIRECTORY)
# Libraries path define
# Add path to local libraries
# Note: the Find<library>.cmake must be placed in an immediate subdirectory of the specific
#library folder
#string(APPEND CMAKE_PREFIX_PATH /opt/homebrew/Cellar/root/6.30.02/include/root)
string(APPEND CMAKE_LIBRARY_PATH /opt/homebrew/Cellar/root/6.30.02/lib/root)

#set(VDT_INCLUDE_DIR /opt/homebrew/Cellar/root/6.30.02/include/root)
#set(VDT_LIBRARY)

#find package section
find_package(ROOT REQUIRED)

#link libraries defines
#Define a set of libraries to be linked
#Variables must have this structure: PROGRAM_LIBRARIES_<combination_name>
set(PROGRAM_LIBRARIES_DEFAULT
        ROOT::Core
        ROOT::Gpad
        ROOT::Graf3d
        ROOT::Graf
        ROOT::Hist
        ROOT::Imt
        ROOT::MathCore
        ROOT::Matrix
        ROOT::MultiProc
        ROOT::Net
        ROOT::Physics
        ROOT::Postscript
        ROOT::RIO
        ROOT::ROOTDataFrame
        ROOT::Rint
        ROOT::Thread
        ROOT::TreePlayer
        ROOT::Tree
        ROOT::Gui
        )
