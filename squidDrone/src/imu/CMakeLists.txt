target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries/i2c  # TODO: switch later to real libraries
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inertial_measurement.cpp
)