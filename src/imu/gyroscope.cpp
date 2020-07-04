#include "gyroscope.hpp"

namespace imu {

void Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {
  sensitivity = gyroscope_sensitivity;
}

}  // namespace imu