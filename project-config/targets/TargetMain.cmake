# Main target configuration file
# Define config for main target

add_executable(program.bin ${PROGRAM_MODULES_MAIN})
target_link_libraries(program.bin ${PROGRAM_LIBRARIES_DEFAULT})