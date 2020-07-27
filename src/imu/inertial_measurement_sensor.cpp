#include "inertial_measurement_sensor.hpp"

namespace imu {

auto InertialMeasurementSensor::Init(std::uint8_t i2c_address) noexcept -> types::HalError {
  initialized_ = false;
  return types::HalError::CONFIG_ERROR;
}

auto InertialMeasurementSensor::Get(void) noexcept -> types::EuclideanVector<float> {
  return sensor_values_;
}

auto InertialMeasurementSensor::Update(void) noexcept -> types::HalError {
  return types::HalError::PARAMETER_ERROR;
}

}  // namespace imu