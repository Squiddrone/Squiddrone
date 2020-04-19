#include "mpu9250.hpp"

namespace imu{

  types::GyroscopeSensitivity Mpu9250::GetGyroscopeSensitivity(void) noexcept {
    return gyroscope_sensitivity_;
  }

  types::AccelerometerSensitivity Mpu9250::GetAccelerometerSensitivity(void) noexcept {
    return accelerometer_sensitivity_;
  }
}