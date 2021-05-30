#ifndef MOCK_MAGNETOMETER_HPP_
#define MOCK_MAGNETOMETER_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "magnetometer_interface.hpp"
#include "mock_i2c.hpp"

namespace imu {

class MockMagnetometer : public MagnetometerInterface {
 public:
  MockMagnetometer() : MagnetometerInterface(std::move(std::make_unique<i2c::MockI2C>())) {}
  MOCK_METHOD(types::DriverStatus, Init, (std::uint8_t i2c_address), (noexcept));
  MOCK_METHOD(types::DriverStatus, Update, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<std::int16_t>, Get, (), (noexcept));
};
}  // namespace imu

#endif