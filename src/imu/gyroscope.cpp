#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  sensitivity_ = gyroscope_sensitivity;
  return types::HalError::CONFIG_ERROR;
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return sensitivity_;
}

}  // namespace imu