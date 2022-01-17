target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/little_bee_20_a.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/letodar_2204.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/motor_builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/motor_driver.cpp
)