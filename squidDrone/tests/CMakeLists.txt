
include(AddGoogleTest)
include(BundleAllTests)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR} 
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/types
            ${CMAKE_SOURCE_DIR}/src/propulsion
            ${CMAKE_SOURCE_DIR}/src/imu
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries
            ${CMAKE_SOURCE_DIR}/tests/imu/mock_libraries
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER "tests")
endmacro()

package_add_test(euclidean_vector types/euclidean_vector_test.cpp)
package_add_test(abstract_esc propulsion/esc_test.cpp)
package_add_test(concrete_esc_little_bee_20_a 
    propulsion/little_bee_20_a_test.cpp 
    ${CMAKE_SOURCE_DIR}/src/propulsion/little_bee_20_a.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/stm32g4xx_hal_tim.c
)
target_compile_definitions(concrete_esc_little_bee_20_a PRIVATE STM32G431xx)
package_add_test(imu_interface 
    imu/imu_interface_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/imu/inertial_measurement.cpp
)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        euclidean_vector
        abstract_esc
        concrete_esc_little_bee_20_a
        imu_interface
)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            all_tests
    )
endif(CODE_COVERAGE)
