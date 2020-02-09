add_subdirectory(mcu_config)
add_subdirectory(types)
add_subdirectory(propulsion)

target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)