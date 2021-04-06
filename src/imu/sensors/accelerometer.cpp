#include "accelerometer.hpp"

namespace imu {

auto Accelerometer::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  sensor_data_register = imu::ACCEL_MEASUREMENT_DATA;
  register_data_length_in_bytes = 6;
  config_register = imu::ACCEL_CONFIG;
  little_endian = true;

  return SensorWithSensitivity::Init(i2c_address);
}

auto Accelerometer::Update(void) noexcept -> types::DriverStatus {
  if (SensorVector::Update() == types::DriverStatus::OK) {
    auto adc_2_accel = GetFactorADC2Accelerometer();
    sensor_values_.x = static_cast<std::int16_t>(adc_2_accel * static_cast<float>(sensor_values_.x));
    sensor_values_.y = static_cast<std::int16_t>(adc_2_accel * static_cast<float>(sensor_values_.y));
    sensor_values_.z = static_cast<std::int16_t>(adc_2_accel * static_cast<float>(sensor_values_.z));
    return types::DriverStatus::OK;
  } else {
    return types::DriverStatus::HAL_ERROR;
  }
}

auto Accelerometer::GetFactorADC2Accelerometer(void) noexcept -> float {
  auto accel_resolution = 0.0f;

  switch (sensitivity_) {
    case types::ImuSensitivity::FINEST:
      accel_resolution = 16.0;
      break;
    case types::ImuSensitivity::FINER:
      accel_resolution = 8.0;
      break;
    case types::ImuSensitivity::ROUGHER:
      accel_resolution = 4.0;
      break;
    case types::ImuSensitivity::ROUGHEST:
      accel_resolution = 2.0;
      break;
  }
  return static_cast<float>(accel_resolution / static_cast<float>(INT16_MAX));
}

}  // namespace imu