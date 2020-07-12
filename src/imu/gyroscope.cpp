#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  sensitivity = gyroscope_sensitivity;
  return types::HalError::CONFIG_ERROR;
}

}  // namespace imu