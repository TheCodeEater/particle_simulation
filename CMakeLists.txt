cmake_minimum_required(VERSION 3.16)
project(Root_template_project VERSION 0.0.1)

#test configuration
include(CTest)

# Defines
# Define variables and stuff needed later
# For best practice, avoid defining here variables needed in the included scripts
# Always write absolute paths, using CMAKE_SOURCE_DIR to get the project root

#set config base path
set(CONFIG_BUILD_DIR ${CMAKE_SOURCE_DIR}/project-config)

# Config files
# Include configuration files
include(${CMAKE_SOURCE_DIR}/project-config/Settings.cmake)

# Compiler flags
# NOTE: must be placed after config as variables needed are defined there
include(${CONFIG_BUILD_DIR}/CompilerFlags.cmake)

#Libraries
include(${CONFIG_BUILD_DIR}/Dependencies.cmake)

#Configure project files
include(${CONFIG_BUILD_DIR}/Configuration.cmake)

#Targets
#Include target configuration
include(${CONFIG_BUILD_DIR}/Targets.cmake)
