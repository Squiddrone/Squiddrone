
add_testpackage(TEST_NAME 
                    com_interface 
                SOURCES 
                    com_interface_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/com
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/com/mock_libraries
)

add_testpackage(TEST_NAME 
                    com_message_buffer 
                SOURCES 
                    com_message_buffer_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/com/com_message_buffer.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/com
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/com/mock_libraries
)

add_testpackage(TEST_NAME 
                    com_nrf24l01_spi_ptotocol 
                SOURCES 
                    com_nrf24l01_spi_protocol_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/com/com_nrf24l01_spi_protocol.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/com
                    ${CMAKE_SOURCE_DIR}/src/types
                    ${CMAKE_SOURCE_DIR}/tests/com/mock_libraries
)
