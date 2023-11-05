# Program modules configuration
# Defines variables that hold source/header files to be compilated
# Variables must have this structure: PROGRAM_MODULES_<module_name>_<SRC/H>
# Main is the only exception
# Do not recall data from libraries.cmake, unless you edit the CMakelists.txt appropriately
# Note: use this only for program-specific code, if you plan to use shared components,
# add them as a library
include_guard(DIRECTORY)
 set(PROGRAM_MODULES_MAIN_SRC
         ${PROGRAM_SOURCES}/main.cpp)

set(PROGRAM_MODULES_MAIN_H
        ${PROGRAM_HEADERS}/Definitions.hpp)

set(PROGRAM_MODULES_PARTICLES_H
        ${PROGRAM_HEADERS}/particles/Particle.hpp
        ${PROGRAM_HEADERS}/particles/ParticleType.hpp
        ${PROGRAM_HEADERS}/particles/ResonanceType.hpp)

set(PROGRAM_MODULES_PARTICLES_SRC
        ${PROGRAM_SOURCES}/particles/Particle.cpp
        ${PROGRAM_SOURCES}/particles/ParticleType.cpp
        ${PROGRAM_SOURCES}/particles/ResonanceType.cpp)

set(PROGRAM_MODULES_ANALYSER_H
        ${ANALYSER_HEADERS}/particleAnalyser.hpp
        ${ANALYSER_HEADERS}/analyserGraphics.hpp
        ${ANALYSER_HEADERS}/dataStructures/signalFitResult.hpp
        ${ANALYSER_HEADERS}/dataStructures/genCheckResult.hpp)

set(PROGRAM_MODULES_ANALYSER_SRC
        ${ANALYSER_SOURCES}/analyser.cpp
        ${ANALYSER_SOURCES}/particleAnalyser.cpp
        ${ANALYSER_SOURCES}/analyserGraphics.cpp
        ${ANALYSER_SOURCES}/dataStructures/genCheckResult.cpp)

set(PROGRAM_MODULES_STORAGE_SRC
        ${ANALYSER_SOURCES}/particleStorage.cpp)

set(PROGRAM_MODULES_STORAGE_H
        ${ANALYSER_HEADERS}/particleStorage.hpp)

#Example
# set(PROGRAM_MODULES_GRAPHICS_SRC ${PROGRAM_SOURCES}/graphics.cpp)
# set(PROGRAM_MDOULES_GRAPHICS_H ${PROGRAM_HEADERS}/graphics.hpp)

#General header variables
set(PROGRAM_MODULES_ALL_HEADERS
        ${PROGRAM_MDOULES_MAIN_H}
        ${PROGRAM_MODULES_PARTICLES_H}
        ${PROGRAM_MODULES_ANALYSER_H}
        ${PROGRAM_MODULES_STORAGE_H})
