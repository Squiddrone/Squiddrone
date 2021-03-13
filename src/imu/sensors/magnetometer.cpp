#include "magnetometer.hpp"

namespace imu {

auto Magnetometer::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::MAGNETOMETER_XOUT_L;
  REGISTER_DATA_LENGTH_IN_BYTES = 7;

  if (SensorGeneral::Init(i2c_address) != types::DriverStatus::OK)
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);
  SetInitData();

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Magnetometer::SetInitData(void) noexcept -> void {
  PowerDownMagnetometer();
  EnterFuseROMAccessMode();
  GetCalibrationValues();
  PowerDownMagnetometer();
  ConfigureForContinousRead();
}

auto Magnetometer::PowerDownMagnetometer(void) noexcept -> void {
  WriteContentIntoRegister(AK8963_CNTL, 0x00);
  utilities::Sleep(10);
}

auto Magnetometer::EnterFuseROMAccessMode(void) noexcept -> void {
  WriteContentIntoRegister(AK8963_CNTL, 0x0F);
  utilities::Sleep(10);
}

auto Magnetometer::ConfigureForContinousRead(void) noexcept -> void {
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  WriteContentIntoRegister(AK8963_CNTL, 0x12);  // Set magnetometer data resolution and sample ODR
  utilities::Sleep(10);
}

auto Magnetometer::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (!IsMagnetometerMeasurementReady())
    return types::DriverStatus::HAL_ERROR;

  if (SensorVector::Update() == types::DriverStatus::OK) {
    if (HasMagnetometerOverflow(raw_values_.at(6)))
      return types::DriverStatus::HAL_ERROR;

    if (ImuConnectionSuccessful()) {
      SetSensorValues(
          ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(1), raw_values_.at(0)),
          ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(3), raw_values_.at(2)),
          ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(5), raw_values_.at(4)));

      const auto adc_2_magnetometer = GetFactorADC2Magnetometer();
      sensor_values_.x = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.x * calibration_values_.x);
      sensor_values_.y = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.y * calibration_values_.y);
      sensor_values_.z = static_cast<std::int16_t>(adc_2_magnetometer * (float)sensor_values_.z * calibration_values_.z);
      return types::DriverStatus::OK;
    }
  }

  return types::DriverStatus::HAL_ERROR;
}

auto Magnetometer::IsMagnetometerMeasurementReady(void) noexcept -> bool {
  auto st1_register = std::make_unique<utilities::Byte>(ReadContentFromRegister(imu::AK8963_ST1, 1).at(0));
  return st1_register->IsBitHigh(0);
}

auto Magnetometer::HasMagnetometerOverflow(const std::uint8_t st2_register_value) noexcept -> bool {
  auto st2_register = std::make_unique<utilities::Byte>(st2_register_value);
  return st2_register->IsBitHigh(3);
}

auto Magnetometer::GetFactorADC2Magnetometer(void) noexcept -> float {
  return static_cast<float>(MAX_MAGNETIC_FLUX_IN_MICRO_TESLA / MAX_MAGNETIC_MEASUREMENT_IN_DIGIT_16BIT);
}

auto Magnetometer::GetCalibrationValues(void) noexcept -> void {
  const std::vector<std::uint8_t> raw_calibration_values = ReadContentFromRegister(imu::AK8963_ASAX, 3);

  calibration_values_.x = AdjustSensitivity(raw_calibration_values[0]);
  calibration_values_.y = AdjustSensitivity(raw_calibration_values[1]);
  calibration_values_.z = AdjustSensitivity(raw_calibration_values[2]);
}

auto Magnetometer::AdjustSensitivity(std::uint8_t sensitivity_adjustment_value) noexcept -> float {
  // for formula see MPU-9255 Register Map, Revision 1.0, p. 53
  return static_cast<float>((sensitivity_adjustment_value - 128) * 0.5 / 128.0 + 1.0);
}

}  // namespace imu