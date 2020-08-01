#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<float> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Update(void) noexcept -> types::HalError {
  return types::HalError::PARAMETER_ERROR;
}

}  // namespace imu