
add_testpackage(TEST_NAME 
                    spi_interface
                SOURCES 
                    spi_interface_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/spi
                    ${CMAKE_SOURCE_DIR}/src/types
)

add_testpackage(TEST_NAME 
                    spi
                SOURCES 
                    spi_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/spi/spi.cpp
                    ${CMAKE_SOURCE_DIR}/tests/spi/mock_libraries/gpio_config.c
                    ${CMAKE_SOURCE_DIR}/tests/spi/mock_libraries/spi_config.c
                    ${CMAKE_SOURCE_DIR}/tests/spi/mock_libraries/stm32g4xx_hal.c
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/spi
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/spi/mock_libraries
)
