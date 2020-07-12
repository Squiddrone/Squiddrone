#ifndef SRC_GYROSCOPE_HPP_
#define SRC_GYROSCOPE_HPP_

#include "gyroscope_sensitivity.hpp"
#include "inertial_measurement_sensor.hpp"

namespace imu {

class Gyroscope final : public InertialMeasurementSensor {
 public:
  Gyroscope() = delete;
  ~Gyroscope() = default;

  explicit Gyroscope(std::unique_ptr<i2c::I2C> i2c_handler, types::GyroscopeSensitivity gyroscope_sensitivity) : InertialMeasurementSensor(std::move(i2c_handler)), sensitivity(gyroscope_sensitivity) {}
  auto SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError;

 private:
  types::GyroscopeSensitivity sensitivity;
};

}  // namespace imu

#endif