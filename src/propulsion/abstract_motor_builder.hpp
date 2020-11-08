#ifndef SRC_PROPULSION_ABSTRACT_MOTOR_BUILDER_HPP_
#define SRC_PROPULSION_ABSTRACT_MOTOR_BUILDER_HPP_

#include <memory>
#include "motor.hpp"
#ifndef UNIT_TEST
#include "propulsion_hardware_config.hpp"
#else
#include "propulsion_hardware_config_mock.hpp"
#endif

namespace propulsion

{
class AbstractMotorBuilder {
 public:
  AbstractMotorBuilder() = default;
  virtual ~AbstractMotorBuilder() = default;
  /**
   * @brief Abstract method to construct a Motor object
   * 
   * @param motor_config The information by which it can be determined which Motor to build
   * @return std::unique_ptr<Motor> A pointer to said Motor. Nullptr on error
   */
  virtual auto Create(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> std::unique_ptr<Motor> = 0;
};

}  // namespace propulsion

#endif