#ifndef SRC_MPU9255_REGISTERS_HPP_
#define SRC_MPU9255_REGISTERS_HPP_

#include <cstdint>

namespace imu {

static constexpr std::uint8_t WHO_AM_I_MPU9255_ADDRESS = 0x68;

static constexpr std::uint8_t WHO_AM_I_MPU9255_REGISTER = 0x75;
static constexpr std::uint8_t WHO_AM_I_MPU9255_VALUE = 0x73;

}  // namespace imu

#endif