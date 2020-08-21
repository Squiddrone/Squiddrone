
include(AddGoogleTest)
include(BundleAllTests)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/com
            ${CMAKE_SOURCE_DIR}/src/types
            ${CMAKE_SOURCE_DIR}/src/propulsion
            ${CMAKE_SOURCE_DIR}/src/imu
            ${CMAKE_SOURCE_DIR}/src/i2c
            ${CMAKE_SOURCE_DIR}/src/spi
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries/com
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c
            ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER "tests")
    target_compile_definitions(${TESTNAME} PRIVATE UNIT_TEST STM32G431xx)
endmacro()

package_add_test(euclidean_vector types/euclidean_vector_test.cpp)
package_add_test(abstract_esc propulsion/esc_test.cpp)

package_add_test(concrete_esc_little_bee_20_a 
    propulsion/little_bee_20_a_test.cpp 
    ${CMAKE_SOURCE_DIR}/src/propulsion/little_bee_20_a.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion/stm32g4xx_hal_tim.c
)

package_add_test(abstract_motor propulsion/motor_test.cpp)
package_add_test(letodar_2204 propulsion/letodar_2204_test.cpp
    ${CMAKE_SOURCE_DIR}/src/propulsion/letodar_2204.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion/esc_mock.cpp
)


package_add_test(imu_interface 
    imu/imu_interface_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/imu/inertial_measurement.cpp
    ${CMAKE_SOURCE_DIR}/src/i2c/i2c.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu/mpu9250.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/stm32g4xx_hal.c
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/i2c_config.c
)

package_add_test(i2c
    i2c/i2c_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/i2c/i2c.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/stm32g4xx_hal.c
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/i2c_config.c
)

package_add_test(com_interface
    com/com_interface_tests.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/com/com_message_buffer_mock.cpp
)

package_add_test(com_message_buffer
    com/com_message_buffer_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/com/com_message_buffer.cpp
)

package_add_test(propulsion_hardware_config_type propulsion/propulsion_hardware_config_test.cpp)

package_add_test(motor_builder propulsion/motorbuilder_test.cpp
    ${CMAKE_SOURCE_DIR}/src/propulsion/motor_builder.cpp
)

package_add_test(spi_interface
    spi/spi_interface_tests.cpp
)

package_add_test(imu_sensors_gyroscope
    ${CMAKE_SOURCE_DIR}/src/imu/inertial_measurement_sensor.cpp
    ${CMAKE_SOURCE_DIR}/src/imu/gyroscope.cpp
    ${CMAKE_SOURCE_DIR}/tests/imu/imu_gyroscope_tests.cpp
)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 GTEST_SHUFFLE=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        euclidean_vector
        abstract_esc
        concrete_esc_little_bee_20_a
        imu_interface
        imu_sensors_gyroscope
        abstract_motor
        letodar_2204
        propulsion_hardware_config_type
        motor_builder
        com_interface
        com_message_buffer
        i2c
        spi_interface
)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE GTEST_SHUFFLE=1 ctest -j ${n_cores}
        DEPENDENCIES
            all_tests
    )
endif(CODE_COVERAGE)
