#
#Configure main target
include(ProgramModules.cmake)

add_executable(main.bin ${PROGRAM_MODULES_MAIN})
target_link_libraries(main.bin ${PROGRAM_LIBRARIES_DEFAULT})