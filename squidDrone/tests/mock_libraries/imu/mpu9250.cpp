#include "mpu9250.hpp"

namespace imu{

  types::GyroscopeSensitivity Mpu9250::GetGyroscopeSensitivity(void) noexcept {
    return Mpu9250::gyroscope_sensitivity;
  }

  types::AccelerometerSensitivity Mpu9250::GetAccelerometerSensitivity(void) noexcept {
    return Mpu9250::accelerometer_sensitivity;
  }
}