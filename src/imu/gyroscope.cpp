#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::HalError {
  i2c_address_ = i2c_address;

  if (!Mpu9255Detected()) {
    return types::HalError::CONFIG_ERROR;
  }

  initialized_ = true;
  sensor_values_.x = 0;
  sensor_values_.y = 0;
  sensor_values_.z = 0;
  return types::HalError::WORKING;
}

auto Gyroscope::Get(void) noexcept -> types::EuclideanVector<float> {
  return sensor_values_;
}

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  sensitivity_ = gyroscope_sensitivity;
  if (!initialized_)
    return types::HalError::CONFIG_ERROR;

  return types::HalError::WORKING;
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return sensitivity_;
}

}  // namespace imu