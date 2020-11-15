function(add_testpackage)
    set(options)
    set(oneValueArgs TEST_NAME)
    set(multiValueArgs SOURCES TEST_INCLUDE_DIRECTORIES)
    cmake_parse_arguments(
        TESTPACKAGE "${options}" "${oneValueArgs}"
        "${multiValueArgs}" ${ARGN} 
    )

    add_executable(${TESTPACKAGE_TEST_NAME} ${TESTPACKAGE_SOURCES})
    target_include_directories(${TESTPACKAGE_TEST_NAME} 
        PRIVATE
            ${TESTPACKAGE_TEST_INCLUDE_DIRECTORIES}
    )
    target_link_libraries(${TESTPACKAGE_TEST_NAME} gtest gmock gtest_main)
    add_test(NAME ${TESTPACKAGE_TEST_NAME} COMMAND ${TESTPACKAGE_TEST_NAME} --gtest_output=xml:${TESTPACKAGE_TEST_NAME}.xml)
    set_target_properties(${TESTPACKAGE_TEST_NAME} PROPERTIES FOLDER "tests")
    target_compile_definitions(${TESTPACKAGE_TEST_NAME} PRIVATE UNIT_TEST STM32G431xx)
endfunction()