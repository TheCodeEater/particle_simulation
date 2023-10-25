# Target configuration file
# Targets should be defined in their own cmake file inside targets
# Alternatively, they can be set up here, along with extra logic

#Add subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/main)


#Add tests
if(BUILD_TESTING)
    add_subdirectory(${PROGRAM_TEST_UNIT}/sample) #add example test
endif()