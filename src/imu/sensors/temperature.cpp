#include "temperature.hpp"

namespace imu {

auto Temperature::Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::TEMP_OUT_H;
  REGISTER_DATA_LENGTH_IN_BYTES = 2;

  if (SensorGeneral::Init(i2c_address) != types::DriverStatus::OK)
    return types::DriverStatus::HAL_ERROR;

  SetSensorValue(0);

  initialized_ = true;
  return types::DriverStatus::OK;
}

auto Temperature::Update(void) noexcept -> types::DriverStatus {
  if (InertialMeasurementSensorSingleValue::Update() == types::DriverStatus::OK) {
    sensor_value_ = CalculateTempInDegreeFromADC(sensor_value_);
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto Temperature::CalculateTempInDegreeFromADC(const std::int16_t adc_value) noexcept -> std::int16_t {
  constexpr float TEMP_SENSITIVITY = 333.87f;
  constexpr std::int16_t Temp21degC = 21;
  return static_cast<std::int16_t>(adc_value / TEMP_SENSITIVITY + Temp21degC);
}

}  // namespace imu