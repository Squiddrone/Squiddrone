
add_testpackage(TEST_NAME 
                    concrete_esc_little_bee_20_a 
                SOURCES 
                    little_bee_20_a_test.cpp 
                    ${CMAKE_SOURCE_DIR}/src/propulsion/little_bee_20_a.cpp
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries/stm32g4xx_hal_tim.c
                TEST_INCLUDE_DIRECTORIES
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries
)

add_testpackage(TEST_NAME 
                    letodar_2204 
                SOURCES 
                    letodar_2204_test.cpp
                    ${CMAKE_SOURCE_DIR}/src/propulsion/letodar_2204.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries
)

add_testpackage(TEST_NAME 
                    propulsion_hardware_config_type 
                SOURCES 
                    propulsion_hardware_config_test.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries
)

add_testpackage(TEST_NAME 
                    motor_builder 
                SOURCES 
                    motorbuilder_test.cpp
                    ${CMAKE_SOURCE_DIR}/src/propulsion/motor_builder.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries
)

add_testpackage(TEST_NAME 
                    motor_driver 
                SOURCES 
                    motor_driver_test.cpp
                    ${CMAKE_SOURCE_DIR}/src/propulsion/motor_driver.cpp
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries/sleep_mock.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/propulsion
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/propulsion/mock_libraries
)