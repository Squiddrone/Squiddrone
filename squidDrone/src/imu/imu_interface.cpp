#include "imu_interface.hpp"

namespace imu{

  void InertialMeasurementInterface::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {

  }

  types::GyroscopeSensitivity InertialMeasurementInterface::GetGyroscopeSensitivity(void) noexcept {
    return types::GyroscopeSensitivity::ROUGHEST;
  }

  void InertialMeasurementInterface::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {

  }

  types::AccelerometerSensitivity InertialMeasurementInterface::GetAccelerometerSensitivity(void) noexcept {
    return types::AccelerometerSensitivity::ROUGHEST;
  }

}