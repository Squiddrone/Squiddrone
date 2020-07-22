#ifndef SRC_GYROSCOPE_HPP_
#define SRC_GYROSCOPE_HPP_

#include "gyroscope_sensitivity.hpp"
#include "inertial_measurement_sensor.hpp"

namespace imu {

class Gyroscope : public InertialMeasurementSensor {
 public:
  Gyroscope() = delete;
  ~Gyroscope() = default;

  explicit Gyroscope(std::unique_ptr<i2c::I2C> i2c_handler) : InertialMeasurementSensor(std::move(i2c_handler)) {}
  auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity;
  auto SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError;

 private:
  types::GyroscopeSensitivity sensitivity_ = types::GyroscopeSensitivity::FINEST;
};

}  // namespace imu

#endif