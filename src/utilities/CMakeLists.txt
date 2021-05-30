target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/uart_print.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sleep.cpp
)