#ifndef SRC_MPU9255_REGISTERS_HPP_
#define SRC_MPU9255_REGISTERS_HPP_

#include <cstdint>

namespace imu {

// MPU9255 specific registers
static constexpr std::uint8_t MPU9255_ADDRESS = 0x68;
static constexpr std::uint8_t WHO_AM_I_MPU9255_VALUE = 0x73;
static constexpr std::uint8_t WHO_AM_I_MPU9255_REGISTER = 0x75;
static constexpr std::uint8_t INT_PIN_CFG = 0x37;
static constexpr std::uint8_t INT_ENABLE = 0x38;
// AK8963 specific register
static constexpr std::uint8_t AK8963_ADDRESS = 0x0C;
static constexpr std::uint8_t WHO_AM_I_AK8963_VALUE = 0x48;
static constexpr std::uint8_t WHO_AM_I_AK8963_REGISTER = 0x00;
static constexpr std::uint8_t AK8963_CNTL = 0x0A;
static constexpr std::uint8_t AK8963_ASAX = 0x10;
static constexpr std::uint8_t AK8963_ST1 = 0x02;
// Gyroscope specific register
static constexpr std::uint8_t GYRO_CONFIG = 0x1B;
static constexpr std::uint8_t GYRO_MEASUREMENT_DATA = 0x43;
// Accelerometer specific register
static constexpr std::uint8_t ACCEL_CONFIG = 0x1C;
static constexpr std::uint8_t ACCEL_MEASUREMENT_DATA = 0x3B;
// Magnetometer specific register
static constexpr std::uint8_t MAGNETOMETER_MEASUREMENT_DATA = 0x03;
// Temperature sensor specific register
static constexpr std::uint8_t TEMP_MEASUREMENT_DATA = 0x41;

}  // namespace imu

#endif