#include "imu_sensor_single_value.hpp"

namespace imu {

auto InertialMeasurementSensorSingleValue::Update(void) noexcept -> types::DriverStatus {
  SensorGeneral::GetRawValues();

  if (ImuConnectionSuccessful()) {
    SetSensorValue(
        ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(0), raw_values_.at(1)));
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto InertialMeasurementSensorSingleValue::Get(void) noexcept -> std::int16_t {
  return sensor_value_;
}

auto InertialMeasurementSensorSingleValue::SetSensorValue(const std::int16_t new_value) noexcept -> void {
  sensor_value_ = new_value;
}

}  // namespace imu