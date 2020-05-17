#ifndef SRC_PROPULSION_MOTOR_BUILDER_HPP_
#define SRC_PROPULSION_MOTOR_BUILDER_HPP_

#include <memory>

#ifndef UNIT_TEST
#include "propulsion_hardware_config.hpp"
#include "motor.hpp"
#else
#include "propulsion_hardware_config_mock.hpp"
#include "motor_mock.hpp"
#endif

namespace propulsion{
  class MotorBuilder{
    public:
      MotorBuilder() = delete;
      static auto Create(propulsion::PropulsionHardwareConfig motor_config) -> const std::unique_ptr<Motor>;


  };
}
#endif