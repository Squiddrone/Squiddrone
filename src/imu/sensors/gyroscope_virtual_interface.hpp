#ifndef SRC_GYROSCOPE_INTERFACE_HPP_
#define SRC_GYROSCOPE_INTERFACE_HPP_

#include "sensor_with_sensitivity.hpp"

namespace imu {

class GyroscopeInterface : public SensorWithSensitivity {
 public:
  GyroscopeInterface() = delete;
  ~GyroscopeInterface() = default;

  explicit GyroscopeInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorWithSensitivity(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus override = 0;
};

}  // namespace imu

#endif