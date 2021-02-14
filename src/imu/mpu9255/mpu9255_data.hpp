#ifndef SRC_MPU9255_REGISTERS_HPP_
#define SRC_MPU9255_REGISTERS_HPP_

#include <cstdint>

namespace imu {

static constexpr std::uint8_t ACCEL_XOUT_H = 0x3B;
static constexpr std::uint8_t ACCEL_CONFIG = 0x1C;
static constexpr std::uint8_t GYRO_CONFIG = 0x1B;
static constexpr std::uint8_t GYRO_XOUT_H = 0x43;
static constexpr std::uint8_t MAGNETOMETER_XOUT_L = 0x03;
static constexpr std::uint8_t MPU9255_ADDRESS = 0x68;
static constexpr std::uint8_t WHO_AM_I_MPU9255_VALUE = 0x73;
static constexpr std::uint8_t WHO_AM_I_MPU9255_REGISTER = 0x75;
static constexpr std::uint8_t AK8963_ADDRESS = 0x0C;
static constexpr std::uint8_t WHO_AM_I_AK8963_VALUE = 0x48;
static constexpr std::uint8_t WHO_AM_I_AK8963_REGISTER = 0x00;
static constexpr std::uint8_t INT_PIN_CFG = 0x37;
static constexpr std::uint8_t INT_ENABLE = 0x38;
static constexpr std::uint8_t AK8963_CNTL = 0x0A;
static constexpr std::uint8_t TEMP_OUT_H = 0x41;
static constexpr std::uint8_t AK8963_ASAX = 0x10;
}  // namespace imu

#endif