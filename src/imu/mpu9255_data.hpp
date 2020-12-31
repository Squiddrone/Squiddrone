#ifndef SRC_MPU9255_REGISTERS_HPP_
#define SRC_MPU9255_REGISTERS_HPP_

#include <cstdint>

namespace imu {

static constexpr std::uint8_t ACCEL_XOUT_H = 0x3B;
static constexpr std::uint8_t ACCEL_CONFIG = 0x1C;
static constexpr std::uint8_t GYRO_CONFIG = 0x1B;
static constexpr std::uint8_t GYRO_XOUT_H = 0x43;
static constexpr std::uint8_t WHO_AM_I_MPU9255_ADDRESS = 0x68;
static constexpr std::uint8_t WHO_AM_I_MPU9255_VALUE = 0x73;
static constexpr std::uint8_t WHO_AM_I_MPU9255_REGISTER = 0x75;

}  // namespace imu

#endif