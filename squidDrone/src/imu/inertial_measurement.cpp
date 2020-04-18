#include "inertial_measurement.hpp"

namespace imu
{

void InertialMeasurement::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept
{
  mpu9250.SetGyroscopeSensitivity(gyroscope_sensitivity);
}

types::GyroscopeSensitivity InertialMeasurement::GetGyroscopeSensitivity(void) noexcept
{
  return mpu9250.GetGyroscopeSensitivity();
}

void InertialMeasurement::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept
{
  mpu9250.SetAccelerometerSensitivity(accelerometer_sensitivity);
}

types::AccelerometerSensitivity InertialMeasurement::GetAccelerometerSensitivity(void) noexcept
{
  return mpu9250.GetAccelerometerSensitivity();
}

types::EuclideanVector<float> InertialMeasurement::GetGyroscope(void) noexcept
{
  return mpu9250.GetGyroscope();
}

types::EuclideanVector<float> InertialMeasurement::GetAccelerometer(void) noexcept
{
  return mpu9250.GetAccelerometer();
}

types::EuclideanVector<float> InertialMeasurement::GetMagnetometer(void) noexcept
{
  return mpu9250.GetMagnetometer();
}

int InertialMeasurement::GetTemperature(void) noexcept
{
  return mpu9250.GetTemperature();
}

} // namespace imu