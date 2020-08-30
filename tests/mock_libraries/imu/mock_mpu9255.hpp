#ifndef MOCK_MPU9255_HPP_
#define MOCK_MPU9255_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "generic_imu.hpp"
#include "mock_i2c.hpp"

namespace imu {

class MOCKMPU9255 : public GenericInertialMeasurementUnit {
 public:
  MOCKMPU9255() : GenericInertialMeasurementUnit(std::move(std::make_unique<i2c::MOCKI2C>())) {}
  MOCK_METHOD(void, SetGyroscopeSensitivity, (types::ImuSensitivity gyroscope_sensitivity), (noexcept));
  MOCK_METHOD(types::ImuSensitivity, GetGyroscopeSensitivity, (), (noexcept));
  MOCK_METHOD(void, SetAccelerometerSensitivity, (types::ImuSensitivity accelerometer_sensitivity), (noexcept));
  MOCK_METHOD(types::ImuSensitivity, GetAccelerometerSensitivity, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<float>, GetGyroscope, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<float>, GetAccelerometer, (), (noexcept));
  MOCK_METHOD(types::EuclideanVector<float>, GetMagnetometer, (), (noexcept));
  MOCK_METHOD(int, GetTemperature, (), (noexcept));
};
}  // namespace imu

#endif