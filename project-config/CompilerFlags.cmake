#setup compiler flags
#
# Replace C++ standard to the one root is compiled with
# Set CONFIG_AUTODETECT_ROOT_STD to do this automatically
# If unset, defaults to C++17 (the std used at the creation of this template
#
include_guard(GLOBAL) #Compiler options should be processed once

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set C++ std
if (CONFIG_AUTODETECT_ROOT_STD)
    message(FATAL_ERROR "Root c++ std autodetection scripts does not exist!")
else ()
    set(CMAKE_CXX_STANDARD 17)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#Warnings, asan, ubsan
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wpedantic")
#string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined -fno-omit-frame-pointer")
#string(APPEND CMAKE_EXE_LINKER_FLAGS " -fsanitize=address,undefined -fno-omit-frame-pointer")
#set (CMAKE_SHARED_LINKER_FLAGS " -fsanitize=address,undefined -fno-omit-frame-pointer")