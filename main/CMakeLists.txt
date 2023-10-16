#Configure main target
# Get program modules
include(${CONFIG_BUILD_DIR}/ProgramModules.cmake)

# Register the executable
add_executable(main.bin ${PROGRAM_MODULES_MAIN})
target_link_libraries(main.bin ${PROGRAM_LIBRARIES_DEFAULT})