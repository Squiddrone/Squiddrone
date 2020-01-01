
include(AddGoogleTest)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR} 
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/types
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER "tests")
endmacro()

package_add_test(dummy dummy_tests.cpp)
package_add_test(thrust_vector types/thrust_vector_test.cpp)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            dummy
    )
endif(CODE_COVERAGE)
