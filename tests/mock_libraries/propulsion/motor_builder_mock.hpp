#ifndef TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_BUILDER_MOCK_HPP_
#define TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_BUILDER_MOCK_HPP_

#include "motor.hpp"
#include "propulsion_hardware_config.hpp"

namespace propulsion {

/// For now a naive mock, because static methods are death of testability
class MotorBuilder {
 public:
  static auto Create(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> std::unique_ptr<Motor> {
    return nullptr;
  }
};

}  // namespace propulsion

#endif