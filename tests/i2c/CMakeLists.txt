
add_testpackage(TEST_NAME 
                    i2c 
                SOURCES 
                    i2c_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/i2c/i2c.cpp
                    ${CMAKE_SOURCE_DIR}/tests/i2c/mock_libraries/stm32g4xx_hal.c
                    ${CMAKE_SOURCE_DIR}/tests/i2c/mock_libraries/i2c_config.c
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/i2c
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/i2c/mock_libraries
)
