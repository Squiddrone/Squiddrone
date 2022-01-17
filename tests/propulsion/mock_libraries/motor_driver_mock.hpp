#ifndef TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_DRIVER_MOCK_HPP_
#define TEST_MOCK_LIBRARIES_PROPULSION_MOTOR_DRIVER_MOCK_HPP_

#include <array>
#include "abstract_motor_driver.hpp"
#include "error_types.hpp"
#include "gtest/gtest.h"

class MotorDriverMock : public propulsion::AbstractMotorDriver {
 public:
  MotorDriverMock() : propulsion::AbstractMotorDriver() {}
  MOCK_METHOD(const types::DriverStatus, SetMotorSpeed, (const propulsion::MotorPosition which_motor, const float speed), (const, noexcept, override));
  MOCK_METHOD((std::pair<float, types::DriverStatus>), GetMotorSpeed, (const propulsion::MotorPosition which_motor), (const, noexcept, override));
  MOCK_METHOD(const types::DriverStatus, ArmEsc, (), (const, noexcept, override));
};

#endif