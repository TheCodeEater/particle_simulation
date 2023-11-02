include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_ANALYSER analyser.bin)

add_executable(${PROGRAM_TARGET_ANALYSER}
        ${PROGRAM_ALL_HEADERS})

target_sources( ${PROGRAM_TARGET_ANALYSER} PRIVATE
        ${PROGRAM_MODULES_ANALYSER_SRC}
        ${PROGRAM_MODULES_PARTICLES_SRC})


target_include_directories(${PROGRAM_TARGET_ANALYSER} PRIVATE ${PROGRAM_HEADERS})
target_link_libraries(${PROGRAM_TARGET_ANALYSER} ${PROGRAM_LIBRARIES_DEFAULT})

#Generate root dictionary
ROOT_GENERATE_DICTIONARY(analyser_dictionary
        ${PROGRAM_MODULES_ALL_HEADERS}
        MODULE ${PROGRAM_TARGET_ANALYSER}
        LINKDEF ${PROGRAM_BASE}/dictionary/Linkdef.h)