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

  /**
   * @brief A static class which only exists to build a correct Motor object
   */
  class MotorBuilder{
    public:
      /// Ctor is deleted, because it should not be instantiated
      MotorBuilder() = delete;

      /**
       * @brief Constructs a Motor object
       * 
       * @param motor_config The information by which it can be determined what Motor to build
       * @return const std::unique_ptr<Motor> A pointer to said Motor. Nullptr on error
       */
      static auto Create(propulsion::PropulsionHardwareConfig& motor_config) -> std::unique_ptr<Motor>;


  };
}
#endif