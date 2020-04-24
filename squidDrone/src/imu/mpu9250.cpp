#include "mpu9250.hpp"

namespace imu{

  auto Mpu9250::GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity {
    return gyroscope_sensitivity_;
  }

  auto Mpu9250::GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity {
    return accelerometer_sensitivity_;
  }
}