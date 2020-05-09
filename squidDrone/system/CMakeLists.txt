add_subdirectory(hal)
add_subdirectory(cmsis)
add_subdirectory(free_rtos)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/system_stm32g4xx.c
        ${CMAKE_CURRENT_SOURCE_DIR}/sysmem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx_hal_msp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx_it.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32g4xx_hal_timebase_tim.c
)

target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)