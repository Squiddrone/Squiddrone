#include "magnetometer.hpp"

namespace imu {

auto Magnetometer::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  sensor_data_register = imu::MAGNETOMETER_MEASUREMENT_DATA;
  register_data_length_in_bytes = 7;
  little_endian = true;

  if (GeneralSensor::Init(i2c_address) != types::DriverStatus::OK)
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues({0, 0, 0});
  SetInitData();

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Magnetometer::SetInitData(void) noexcept -> void {
  PowerDownMagnetometer();
  EnterFuseROMAccessMode();
  GetCalibrationValues();
  PowerDownMagnetometer();
  ConfigureForContinuousRead();
}

auto Magnetometer::PowerDownMagnetometer(void) noexcept -> void {
  auto cntl_register_value = std::make_unique<utilities::Byte>(0);
  // MODE[3:0]: Operation mode setting -> "0000": Power-down mode
  cntl_register_value->ClearBit(0);
  cntl_register_value->ClearBit(1);
  cntl_register_value->ClearBit(2);
  cntl_register_value->ClearBit(3);
  WriteContentIntoRegister(AK8963_CNTL, cntl_register_value->Get());
  utilities::Sleep(REBOOT_TIME_IN_MS);
}

auto Magnetometer::EnterFuseROMAccessMode(void) noexcept -> void {
  auto cntl_register_value = std::make_unique<utilities::Byte>(0);
  // MODE[3:0]: Operation mode setting -> "1111": Fuse ROM access mode
  cntl_register_value->SetBit(0);
  cntl_register_value->SetBit(1);
  cntl_register_value->SetBit(2);
  cntl_register_value->SetBit(3);
  WriteContentIntoRegister(AK8963_CNTL, cntl_register_value->Get());
  utilities::Sleep(REBOOT_TIME_IN_MS);
}

auto Magnetometer::ConfigureForContinuousRead(void) noexcept -> void {
  auto cntl_register_value = std::make_unique<utilities::Byte>(0);
  // See MPU-9255 Register Map, Revision 1.0, p. 51
  cntl_register_value->SetBit(1);  // Enable continuous mode data acquisition at 8 Hz.
  cntl_register_value->SetBit(4);  // Enable 16 bit resolution
  WriteContentIntoRegister(AK8963_CNTL, cntl_register_value->Get());
  utilities::Sleep(REBOOT_TIME_IN_MS);
}

auto Magnetometer::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (!IsMagnetometerMeasurementReady())
    return types::DriverStatus::HAL_ERROR;

  if (SensorVector::Update() == types::DriverStatus::OK) {
    if (HasMagnetometerOverflow(raw_values_.at(ST2_REGISTER_BYTE)))
      return types::DriverStatus::HAL_ERROR;

    if (ImuConnectionSuccessful()) {
      SetSensorValues(
          ConvertUint8BytesIntoInt16SensorValue(raw_values_));

      const auto adc_2_magnetometer = GetFactorADC2Magnetometer();
      sensor_values_.x = static_cast<std::int16_t>(adc_2_magnetometer * static_cast<float>(sensor_values_.x) * calibration_values_.x);
      sensor_values_.y = static_cast<std::int16_t>(adc_2_magnetometer * static_cast<float>(sensor_values_.y) * calibration_values_.y);
      sensor_values_.z = static_cast<std::int16_t>(adc_2_magnetometer * static_cast<float>(sensor_values_.z) * calibration_values_.z);
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

  calibration_values_.x = AdjustSensitivity(raw_calibration_values[POSITION_X]);
  calibration_values_.y = AdjustSensitivity(raw_calibration_values[POSITION_Y]);
  calibration_values_.z = AdjustSensitivity(raw_calibration_values[POSITION_Z]);
}

auto Magnetometer::AdjustSensitivity(const std::uint8_t sensitivity_adjustment_value) noexcept -> float {
  // for formula see MPU-9255 Register Map, Revision 1.0, p. 53
  return static_cast<float>((sensitivity_adjustment_value - 128) * 0.5 / 128.0 + 1.0);
}

}  // namespace imu