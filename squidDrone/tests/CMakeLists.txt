
include(AddGoogleTest)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR} 
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/types
            ${CMAKE_SOURCE_DIR}/src/propulsion
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER "tests")
endmacro()

package_add_test(thrust_vector types/thrust_vector_test.cpp)
package_add_test(abstract_esc propulsion/esc_test.cpp)
package_add_test(concrete_esc_little_bee_20_a propulsion/little_bee_20_a_test.cpp)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            thrust_vector
            abstract_esc
            concrete_esc_little_bee_20_a
    )
endif(CODE_COVERAGE)
