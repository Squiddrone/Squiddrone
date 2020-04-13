#include "imu_interface.hpp"

namespace imu
{

void InertialMeasurementInterface::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept
{
}

types::GyroscopeSensitivity InertialMeasurementInterface::GetGyroscopeSensitivity(void) noexcept
{
  return types::GyroscopeSensitivity::ROUGHEST;
}

void InertialMeasurementInterface::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept
{
}

types::AccelerometerSensitivity InertialMeasurementInterface::GetAccelerometerSensitivity(void) noexcept
{
  return types::AccelerometerSensitivity::ROUGHEST;
}

types::EuclideanVector<float> InertialMeasurementInterface::GetGyroscope(void) noexcept
{
  types::EuclideanVector<float> value{7.5, 8.5, 9.5};
  return std::move(value);
}

types::EuclideanVector<float> InertialMeasurementInterface::GetAccelerometer(void) noexcept
{
}

types::EuclideanVector<float> InertialMeasurementInterface::GetMagnetometer(void) noexcept
{
}

int InertialMeasurementInterface::GetTemperature(void) noexcept
{
}

} // namespace imu