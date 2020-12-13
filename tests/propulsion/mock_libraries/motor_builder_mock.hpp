#ifndef TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_BUILDER_MOCK_HPP_
#define TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_BUILDER_MOCK_HPP_

#include <memory>
#include "abstract_motor_builder.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "motor.hpp"
#include "propulsion_hardware_config_mock.hpp"

class MockMotorBuilder : public propulsion::AbstractMotorBuilder {
 public:
  MockMotorBuilder() : propulsion::AbstractMotorBuilder() {}
  MOCK_METHOD(std::unique_ptr<propulsion::Motor>, Create, (propulsion::PropulsionHardwareConfig & motor_config), (noexcept, override));
  MOCK_METHOD((std::pair<float, types::DriverStatus>), GetMotorSpeed, (const MotorPosition which_motor), (const, noexcept, override));
  MOCK_METHOD(const types::DriverStatus, ArmEsc, (), (const, noexcept, override));
};

namespace propulsion {
using MotorBuilder = MockMotorBuilder;
}  // namespace propulsion

#endif
