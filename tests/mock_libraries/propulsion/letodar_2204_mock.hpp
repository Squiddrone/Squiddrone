#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_

#include <memory>
#include "esc_mock.hpp"
#include "gmock/gmock.h"
#include "motor.hpp"

namespace propulsion {

class MotorMock : public Motor {
 public:
  MotorMock(std::unique_ptr<propulsion::Esc>) : Motor(nullptr) {}
  MOCK_METHOD(const float, GetCurrentSpeedInPercent, (), (const, noexcept, override));
  MOCK_METHOD(types::DriverStatus, SetSpeedInPercent, (const float), (noexcept, override));
};

using LeTodar2204 = MotorMock;
}  // namespace propulsion
#endif