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
        ${CMAKE_CURRENT_SOURCE_DIR}/cordic_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/crc_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/fmac_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/i2c_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/spi_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/timer_config.c
)
