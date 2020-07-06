#ifndef SRC_PROPULSION_MOTOR_DRIVER_HPP_
#define SRC_PROPULSION_MOTOR_DRIVER_HPP_

#include <array>
#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "motor.hpp"

namespace propulsion {

class MotorDriver {
 public:
  MotorDriver();
  ~MotorDriver() = default;
  auto ApplyThrustVector(types::EuclideanVector<float> thrust_vector) const noexcept -> const types::InputError;
  auto ArmEsc() const noexcept -> const types::HardwareSetupError;

 private:
  static constexpr auto NUMBER_OF_MOTORS_ = 4;
  std::array<std::unique_ptr<Motor>, NUMBER_OF_MOTORS_> motors;
};

}  // namespace propulsion
#endif