#
# Test Cmakelists
# Add targets then add the test (only if unit: GUI test shall not be added to commands)
#
include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_TEST_PARTICLE particleTest.t )

add_executable(${PROGRAM_TARGET_TEST_PARTICLE}
        particleTest.test.cpp
        ${PROGRAM_ALL_HEADERS}) #add also equired program modules

target_sources(${PROGRAM_TARGET_TEST_PARTICLE} PRIVATE
        ${PROGRAM_MODULES_PARTICLES_SRC})

# target_link_libraries#link needed libraries
target_include_directories(${PROGRAM_TARGET_TEST_PARTICLE}
        PRIVATE ${PROGRAM_HEADERS})

#Generate root dictionary if needed

#Register test
add_test(NAME ParticlePrint COMMAND particleTest.t)