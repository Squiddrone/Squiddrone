add_subdirectory(mcu_config)
add_subdirectory(types)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)