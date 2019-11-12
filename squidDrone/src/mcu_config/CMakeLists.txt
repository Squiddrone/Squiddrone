target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/clock_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/mcu_settings.c
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/serial_config.c
)