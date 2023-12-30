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
static constexpr std::uint8_t MPU_CONFIG = 0x1A;
static constexpr std::uint8_t GYRO_CONFIG = 0x1B;
static constexpr std::uint8_t GYRO_MEASUREMENT_DATA = 0x43;
static constexpr std::uint8_t GYRO_X_OFFSET_H = 0x13;
static constexpr std::uint8_t GYRO_X_OFFSET_L = 0x14;
static constexpr std::uint8_t GYRO_Y_OFFSET_H = 0x15;
static constexpr std::uint8_t GYRO_Y_OFFSET_L = 0x16;
static constexpr std::uint8_t GYRO_Z_OFFSET_H = 0x17;
static constexpr std::uint8_t GYRO_Z_OFFSET_L = 0x18;
// Accelerometer specific register
static constexpr std::uint8_t ACCEL_CONFIG = 0x1C;
static constexpr std::uint8_t ACCEL_CONFIG_2 = 0x1D;
static constexpr std::uint8_t ACCEL_MEASUREMENT_DATA = 0x3B;
static constexpr std::uint8_t ACCEL_X_OFFSET_H = 0x77;
static constexpr std::uint8_t ACCEL_X_OFFSET_L = 0x78;
static constexpr std::uint8_t ACCEL_Y_OFFSET_H = 0x7A;
static constexpr std::uint8_t ACCEL_Y_OFFSET_L = 0x7B;
static constexpr std::uint8_t ACCEL_Z_OFFSET_H = 0x7D;
static constexpr std::uint8_t ACCEL_Z_OFFSET_L = 0x7E;
// Magnetometer specific register
static constexpr std::uint8_t MAGNETOMETER_MEASUREMENT_DATA = 0x03;
// Temperature sensor specific register
static constexpr std::uint8_t TEMP_MEASUREMENT_DATA = 0x41;

enum class Axis : std::uint8_t {
  X_AXIS = 0,
  Y_AXIS,
  Z_AXIS,
  ALL
};

namespace gyro {
enum class Bandwidth : std::uint8_t {
  gyro_8800Hz,
  gyro_3600Hz,
  gyro_250Hz,
  gyro_184Hz,
  gyro_92Hz,
  gyro_41Hz,
  gyro_20Hz,
  gyro_10Hz,
  gyro_5Hz
};
}

namespace accel {
enum class Bandwidth : std::uint8_t {
  acc_1113Hz,
  acc_460Hz,
  acc_184Hz,
  acc_92Hz,
  acc_41Hz,
  acc_20Hz,
  acc_10Hz,
  acc_5Hz
};
}

}  // namespace imu

#endif