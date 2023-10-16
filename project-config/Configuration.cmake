#File to configure project source files
include_guard(GLOBAL)

#Process Definitions.hpp.in
if(DEFINED PROGRAM_NAMESPACE)
    configure_file(${PROGRAM_CODE_TEMPLATES}/Definitions.hpp.in
            ${PROGRAM_HEADERS}/Definitions.hpp)
else()
    message(FATAL_ERROR "Application base namespace undefined")
endif()

