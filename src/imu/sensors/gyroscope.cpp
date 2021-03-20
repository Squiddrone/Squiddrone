#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::GYRO_MEASUREMENT_DATA;
  REGISTER_DATA_LENGTH_IN_BYTES = 6;
  CONFIG_REGISTER = imu::GYRO_CONFIG;

  return SensorWithSensitivity::Init(i2c_address);
}

auto Gyroscope::Update(void) noexcept -> types::DriverStatus {
  if (SensorVector::Update() == types::DriverStatus::OK) {
    auto adc_2_gyro = GetFactorADC2Gyro();
    sensor_values_.x = static_cast<std::int16_t>(adc_2_gyro * sensor_values_.x);
    sensor_values_.y = static_cast<std::int16_t>(adc_2_gyro * sensor_values_.y);
    sensor_values_.z = static_cast<std::int16_t>(adc_2_gyro * sensor_values_.z);
    return types::DriverStatus::OK;
  } else {
    return types::DriverStatus::HAL_ERROR;
  }
}

auto Gyroscope::GetFactorADC2Gyro(void) noexcept -> float {
  auto gyro_resolution = 0.0f;

  switch (sensitivity_) {
    case types::ImuSensitivity::FINEST:
      gyro_resolution = 2000.0;
      break;
    case types::ImuSensitivity::FINER:
      gyro_resolution = 1000.0;
      break;
    case types::ImuSensitivity::ROUGHER:
      gyro_resolution = 500.0;
      break;
    case types::ImuSensitivity::ROUGHEST:
      gyro_resolution = 250.0;
      break;
  }
  return static_cast<float>(gyro_resolution / (float)INT16_MAX);
}

}  // namespace imu