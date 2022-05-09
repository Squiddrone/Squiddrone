
add_testpackage(TEST_NAME 
                    euclidean_vector 
                SOURCES 
                    euclidean_vector_test.cpp 
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/types
)

add_testpackage(TEST_NAME 
                    ota_config 
                SOURCES 
                    ota_config_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src/types
)
