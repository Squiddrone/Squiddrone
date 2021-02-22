#include "accelerometer.hpp"

namespace imu {

auto Accelerometer::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::ACCEL_XOUT_H;
  REGISTER_DATA_LENGTH_IN_BYTES = 6;
  CONFIG_REGISTER = imu::ACCEL_CONFIG;

  return InertialMeasurementSensorWithSensitivity::Init(i2c_address);
}

auto Accelerometer::Update(void) noexcept -> types::DriverStatus {
  if (InertialMeasurementSensorVector::Update() == types::DriverStatus::OK) {
    auto adc_2_accel = GetFactorADC2Accelerometer();
    sensor_values_.x = static_cast<std::int16_t>(adc_2_accel * (float)sensor_values_.x);
    sensor_values_.y = static_cast<std::int16_t>(adc_2_accel * (float)sensor_values_.y);
    sensor_values_.z = static_cast<std::int16_t>(adc_2_accel * (float)sensor_values_.z);
    return types::DriverStatus::OK;
  } else {
    return types::DriverStatus::HAL_ERROR;
  }
}

auto Accelerometer::GetFactorADC2Accelerometer(void) noexcept -> float {
  auto accel_resolution = 0;

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
  return static_cast<float>(accel_resolution / (float)INT16_MAX);
}

}  // namespace imu