#ifndef SRC_ACCELEROMETER_INTERFACE_HPP_
#define SRC_ACCELEROMETER_INTERFACE_HPP_

#include "imu_sensor_with_sensitivity.hpp"

namespace imu {

class AccelerometerInterface : public SensorWithSensitivity {
 public:
  AccelerometerInterface() = delete;
  ~AccelerometerInterface() = default;

  explicit AccelerometerInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorWithSensitivity(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus override = 0;
};

}  // namespace imu

#endif