#Configure main target
# Get program modules
include_guard(GLOBAL)
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

set(PROGRAM_TARGET_MAIN main.bin)

# Register the executable
add_executable(${PROGRAM_TARGET_MAIN} ${PROGRAM_MODULES_MAIN})

target_include_directories(${PROGRAM_TARGET_MAIN} PRIVATE ${PROGRAM_HEADERS})
target_link_libraries(${PROGRAM_TARGET_MAIN} ${PROGRAM_LIBRARIES_DEFAULT})

#Generate root dictionary
ROOT_GENERATE_DICTIONARY(main_dictionary
        ${PROGRAM_HEADERS}/MyClass.h
        MODULE ${PROGRAM_TARGET_MAIN}
        LINKDEF dictionary/Linkdef.h)