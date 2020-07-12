#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<float> {
  types::EuclideanVector<float> value{0, 0, 0};
  return value;
}

auto InertialMeasurementSensor::Update(void) noexcept -> types::HalError {
  return types::HalError::PARAMETER_ERROR;
}

}  // namespace imu