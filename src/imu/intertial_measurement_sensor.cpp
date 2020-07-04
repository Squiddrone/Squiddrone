#include "intertial_measurement_sensor.hpp"

namespace imu {

auto Get(void) noexcept -> types::EuclideanVector<float> {
  types::EuclideanVector<float> value{0, 0, 0};
  return value;
}

auto Update(void) noexcept -> void {
}

}  // namespace imu