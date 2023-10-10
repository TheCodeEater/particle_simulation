cmake_minimum_required(VERSION 3.16)
project(Root_template_project VERSION 0.0.1)

# Defines
# Define variables and stuff needed later
# For best practice, avoid defining here variables needed in the included scripts
# Always write absolute paths, using CMAKE_SOURCE_DIR to get the project root

set(CONFIG_BUILD_DIR ${CMAKE_SOURCE_DIR}/project-config)

# Config files
# Include configuration files

include(${CMAKE_SOURCE_DIR}/project-config/Config.cmake)

# Compiler flags
# NOTE: must be placed after config as variables needed are defined there
include(${CONFIG_BUILD_DIR}/CompilerFlags.cmake)

#Program modules
#Configure the various program modules
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

#Libraries
include(${CONFIG_BUILD_DIR}/Libraries.cmake)
