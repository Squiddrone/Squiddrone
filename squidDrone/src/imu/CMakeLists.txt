target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inertial_measurement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mpu9250.cpp
)