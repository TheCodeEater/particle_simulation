# Main target configuration file
# Define config for main target

add_executable(program.bin ${PROGRAM_MODULES_MAIN})
target_link_libraries(program.bin PUBLIC ${PROGRAM_LIBRARIES_DEFAULT})
target_link_libraries(program.bin PUBLIC ${ROOT_LIBRARIES})