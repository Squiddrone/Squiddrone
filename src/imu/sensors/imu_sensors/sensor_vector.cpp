#include "sensor_vector.hpp"

namespace imu {

auto SensorVector::Update(void) noexcept -> types::DriverStatus {
  GeneralSensor::GetRawValues();

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(raw_values_));
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto SensorVector::Get(void) noexcept -> types::EuclideanVector<int16_t> {
  return sensor_values_;
}

auto SensorVector::SetSensorValues(const std::vector<std::int16_t> &sensor_values) noexcept -> void {
  sensor_values_.x = sensor_values.at(POSITION_X);
  sensor_values_.y = sensor_values.at(POSITION_Y);
  sensor_values_.z = sensor_values.at(POSITION_Z);
}

}  // namespace imu