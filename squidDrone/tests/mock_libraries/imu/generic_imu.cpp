#include "generic_imu.hpp"

namespace imu{

  types::GyroscopeSensitivity GenericInertialMeasurementUnit::GetGyroscopeSensitivity(void) noexcept {
    return GenericInertialMeasurementUnit::gyroscope_sensitivity;
  }

}