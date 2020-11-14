
include(AddGoogleTest)
include(BundleAllTests)

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

add_testpackage(TEST_NAME 
                    euclidean_vector 
                SOURCES 
                    types/euclidean_vector_test.cpp 
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/types
)

add_testpackage(TEST_NAME 
                    concrete_esc_little_bee_20_a 
                SOURCES 
                    propulsion/little_bee_20_a_test.cpp 
                    ${CMAKE_SOURCE_DIR}/src/propulsion/little_bee_20_a.cpp
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion/stm32g4xx_hal_tim.c
                TEST_INCLUDE_DIRECTORIES
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion
)

add_testpackage(TEST_NAME 
                    letodar_2204 
                SOURCES 
                    propulsion/letodar_2204_test.cpp
                    ${CMAKE_SOURCE_DIR}/src/propulsion/letodar_2204.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion
)

add_testpackage(TEST_NAME 
                    imu_interface 
                SOURCES 
                    imu/imu_interface_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/imu/inertial_measurement.cpp
                    ${CMAKE_SOURCE_DIR}/src/imu/mpu9255.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/imu
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/src/i2c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c
)

add_testpackage(TEST_NAME 
                    i2c 
                SOURCES 
                    i2c/i2c_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/i2c/i2c.cpp
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/stm32g4xx_hal.c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c/i2c_config.c
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/i2c
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c
)

#add_testpackage(TEST_NAME 
#                    com_interface 
#                SOURCES 
#                    com/com_interface_tests.cpp
#                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/com/com_message_buffer_mock.cpp
#                TEST_INCLUDE_DIRECTORIES 
#                    ${CMAKE_SOURCE_DIR}/src/com
#                    ${CMAKE_SOURCE_DIR}/src/types
#                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/com
#)

#add_testpackage(TEST_NAME 
#                    com_message_buffer 
#                SOURCES 
#                    com/com_message_buffer_tests.cpp
#                    ${CMAKE_SOURCE_DIR}/src/com/com_message_buffer.cpp
#                TEST_INCLUDE_DIRECTORIES 
#                    ${CMAKE_SOURCE_DIR}/src/com
#                    ${CMAKE_SOURCE_DIR}/src/types
#                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/com
#)

add_testpackage(TEST_NAME 
                    propulsion_hardware_config_type 
                SOURCES 
                    propulsion/propulsion_hardware_config_test.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion
)

add_testpackage(TEST_NAME 
                    motor_builder 
                SOURCES 
                    propulsion/motorbuilder_test.cpp
                    ${CMAKE_SOURCE_DIR}/src/propulsion/motor_builder.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/propulsion
)

add_testpackage(TEST_NAME 
                    spi_interface
                SOURCES 
                    spi/spi_interface_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/spi
                    ${CMAKE_SOURCE_DIR}/src/types
)

add_testpackage(TEST_NAME 
                    spi
                SOURCES 
                    spi/spi_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/spi/spi.cpp
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/spi/gpio_config.c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/spi/spi_config.c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/spi/stm32g4xx_hal.c
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/spi
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/spi
)

add_testpackage(TEST_NAME 
                    imu_sensors_gyroscope
                SOURCES 
                    ${CMAKE_SOURCE_DIR}/src/imu/imu_sensor.cpp
                    ${CMAKE_SOURCE_DIR}/src/imu/imu_sensor_with_sensitivity.cpp
                    ${CMAKE_SOURCE_DIR}/src/imu/gyroscope.cpp
                    ${CMAKE_SOURCE_DIR}/tests/imu/imu_gyroscope_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/src/imu
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/src/i2c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c
)

add_testpackage(TEST_NAME 
                    utilities_byte
                SOURCES 
                    ${CMAKE_SOURCE_DIR}/tests/utilities/utilities_byte_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
)

add_testpackage(TEST_NAME 
                    imu_mpu9255
                SOURCES 
                    ${CMAKE_SOURCE_DIR}/src/imu/mpu9255.cpp
                    ${CMAKE_SOURCE_DIR}/tests/imu/imu_mpu9255_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/imu
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/src/i2c
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c
)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 GTEST_REPEAT=3 GTEST_SHUFFLE=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        euclidean_vector
        concrete_esc_little_bee_20_a
        imu_interface
        imu_sensors_gyroscope
        letodar_2204
        propulsion_hardware_config_type
        motor_builder
        #com_interface
        #com_message_buffer
        i2c
        spi_interface
        spi
        utilities_byte
        imu_mpu9255
)

if(CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE GTEST_SHUFFLE=1 ctest -j ${n_cores}
        DEPENDENCIES
            all_tests
    )
endif(CODE_COVERAGE)
