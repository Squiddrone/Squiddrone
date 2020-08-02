#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::HalError {
  i2c_address_ = i2c_address;

  if (!Mpu9255Detected()) {
    return types::HalError::CONFIG_ERROR;
  }

  initialized_ = false;
  return types::HalError::CONFIG_ERROR;
}

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  sensitivity_ = gyroscope_sensitivity;
  return types::HalError::CONFIG_ERROR;
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return sensitivity_;
}

}  // namespace imu