function(SETUP_ALLTESTS_TARGET)

    set(options NONE)
    set(oneValueArgs NAME)
    set(multiValueArgs EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES)
    cmake_parse_arguments(AllTests "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Setup target
    add_custom_target(${AllTests_NAME}
        # Run tests
        COMMAND ${AllTests_EXECUTABLE} ${AllTests_EXECUTABLE_ARGS}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS ${AllTests_DEPENDENCIES}
    )
endfunction()