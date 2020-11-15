
add_testpackage(TEST_NAME 
                    spi_interface
                SOURCES 
                    spi_interface_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/spi
                    ${CMAKE_SOURCE_DIR}/src/types
)