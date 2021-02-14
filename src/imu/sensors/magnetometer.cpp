#include "magnetometer.hpp"

namespace imu {

auto Magnetometer::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::MAGNETOMETER_XOUT_L;
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!AK8963Detected())
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);
  GetCalibrationValues();

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Magnetometer::Update(void) noexcept -> types::DriverStatus {
  if (InertialMeasurementSensor::Update() == types::DriverStatus::OK) {
    auto adc_2_magnetometer = GetFactorADC2Magnetometer();
    sensor_values_.x = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.x);
    sensor_values_.y = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.y);
    sensor_values_.z = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.z);
    return types::DriverStatus::OK;
  } else {
    return types::DriverStatus::HAL_ERROR;
  }
}

auto Magnetometer::GetFactorADC2Magnetometer(void) noexcept -> float {
  return static_cast<float>(10.0 * 4912.0 / 32768.0);  // at the moment fix at 16Bit setting
}

auto Magnetometer::GetCalibrationValues(void) noexcept -> void {
  std::vector<std::uint8_t> raw_calibration_values = ReadContentFromRegister(imu::AK8963_ASAX, 3);

  calibration_values_.x = static_cast<float>((raw_calibration_values[0] - 128) / 256.0 + 1.0);
  calibration_values_.y = static_cast<float>((raw_calibration_values[1] - 128) / 256.0 + 1.0);
  calibration_values_.z = static_cast<float>((raw_calibration_values[2] - 128) / 256.0 + 1.0);
}

}  // namespace imu