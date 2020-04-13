#include "inertial_measurement.hpp"

namespace imu
{

void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept
{
}

types::GyroscopeSensitivity InertialMeasurement::GetGyroscopeSensitivity(void) noexcept
{
  return types::GyroscopeSensitivity::ROUGHEST;
}

void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept
{
}

types::AccelerometerSensitivity InertialMeasurement::GetAccelerometerSensitivity(void) noexcept
{
  return types::AccelerometerSensitivity::ROUGHEST;
}

types::EuclideanVector<float> InertialMeasurement::GetGyroscope(void) noexcept
{
  //types::EuclideanVector<float> value{7.5, 8.5, 9.5};
  //return value;
}

types::EuclideanVector<float> InertialMeasurement::GetAccelerometer(void) noexcept
{
}

types::EuclideanVector<float> InertialMeasurement::GetMagnetometer(void) noexcept
{
}

int InertialMeasurement::GetTemperature(void) noexcept
{
}

} // namespace imu