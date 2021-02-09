#include "temperature.hpp"

namespace imu {

auto Temperature::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::TEMP_OUT_H;
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected())
    return types::DriverStatus::HAL_ERROR;

  sensor_value_ = 0;

  if (ImuConnectionFailed())
    return types::DriverStatus::HAL_ERROR;

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Temperature::Update_(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  const std::uint16_t REGISTER_DATA_LENGTH = 2;
  std::vector<uint8_t> measurement_values = ReadContentFromRegister(SENSOR_DATA_REGISTER, REGISTER_DATA_LENGTH);

  if (ImuConnectionSuccessful()) {
    auto adc_value = ConvertUint8BytesIntoInt16SensorValue(measurement_values.at(0), measurement_values.at(1));
    sensor_value_ = CalculateTempInDegreeFromADC(adc_value);
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto Temperature::CalculateTempInDegreeFromADC(std::int16_t adc_value) noexcept -> std::int16_t {
  constexpr float TEMP_SENSITIVITY = 333.87;
  constexpr std::int16_t Temp21degC = 21;
  return static_cast<std::int16_t>(adc_value / TEMP_SENSITIVITY + Temp21degC);
}

auto Temperature::Get_(void) noexcept -> std::int16_t {
  return sensor_value_;
}

}  // namespace imu