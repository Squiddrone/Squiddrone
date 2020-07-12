target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/i2c
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries/imu
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inertial_measurement.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gyroscope.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/inertial_measurement_sensor.cpp
)