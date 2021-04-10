#ifndef MOCK_MPU9255_HPP_
#define MOCK_MPU9255_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "generic_imu.hpp"
#include "mock_i2c.hpp"

namespace imu {

class MockMpu9255 : public GenericInertialMeasurementUnit {
 public:
  MockMpu9255() : GenericInertialMeasurementUnit(std::move(std::make_unique<i2c::MockI2C>())) {}
  MOCK_METHOD(types::DriverStatus, Init, (), (noexcept));
  MOCK_METHOD(types::DriverStatus, Update, (), (noexcept));
  MOCK_METHOD(types::DriverStatus, SetGyroscopeSensitivity, (types::ImuSensitivity gyroscope_sensitivity), (noexcept));
  MOCK_METHOD(types::ImuSensitivity, GetGyroscopeSensitivity, (), (noexcept));
  MOCK_METHOD(types::DriverStatus, SetAccelerometerSensitivity, (types::ImuSensitivity accelerometer_sensitivity), (noexcept));
  MOCK_METHOD(types::ImuSensitivity, GetAccelerometerSensitivity, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<std::int16_t>, GetGyroscope, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<std::int16_t>, GetAccelerometer, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<std::int16_t>, GetMagnetometer, (), (noexcept));
  MOCK_METHOD(int, GetTemperature, (), (noexcept));
};
}  // namespace imu

#endif