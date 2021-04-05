#include "sensor_vector.hpp"

namespace imu {

auto SensorVector::Update(void) noexcept -> types::DriverStatus {
  GeneralSensor::GetRawValues();

  if (ImuConnectionSuccessful()) {
    SetSensorValues(
        ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(0), raw_values_.at(1)),
        ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(2), raw_values_.at(3)),
        ConvertUint8BytesIntoInt16SensorValue(raw_values_.at(4), raw_values_.at(5)));
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto SensorVector::Get(void) noexcept -> types::EuclideanVector<int16_t> {
  return sensor_values_;
}

auto SensorVector::SetSensorValues(const std::int16_t x, const std::int16_t y, const std::int16_t z) noexcept -> void {
  sensor_values_.x = x;
  sensor_values_.y = y;
  sensor_values_.z = z;
}

}  // namespace imu