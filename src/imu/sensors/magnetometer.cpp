#include "magnetometer.hpp"

namespace imu {

auto Magnetometer::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::MAGNETOMETER_XOUT_L;
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!AK8963Detected())
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);
  SetInitData();

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Magnetometer::SetInitData(void) -> void {
  Write({AK8963_CNTL, 0x00});  // Power down magnetometer
  utilities::Sleep(10);
  Write({AK8963_CNTL, 0x0F});  // Enter Fuse ROM access mode
  utilities::Sleep(10);
  GetCalibrationValues();
  Write({AK8963_CNTL, 0x00});  // Power down magnetometer
  utilities::Sleep(10);
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  Write({AK8963_CNTL, 1 << 4 | 0x02});  // Set magnetometer data resolution and sample ODR
}

auto Magnetometer::Update(void) noexcept -> types::DriverStatus {
  if (InertialMeasurementSensor::Update() == types::DriverStatus::OK) {
    auto adc_2_magnetometer = GetFactorADC2Magnetometer();
    sensor_values_.x = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.x * calibration_values_.x);
    sensor_values_.y = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.y * calibration_values_.y);
    sensor_values_.z = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.z * calibration_values_.z);
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

  calibration_values_.x = static_cast<float>((raw_calibration_values[0] - 128) * 0.5 / 128.0 + 1.0);
  calibration_values_.y = static_cast<float>((raw_calibration_values[1] - 128) * 0.5 / 128.0 + 1.0);
  calibration_values_.z = static_cast<float>((raw_calibration_values[2] - 128) * 0.5 / 128.0 + 1.0);
}

}  // namespace imu