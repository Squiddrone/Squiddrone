#ifndef SRC_TEMPERATURE_INTERFACE_HPP_
#define SRC_TEMPERATURE_INTERFACE_HPP_

#include "sensor_single_value.hpp"

namespace imu {

class TemperatureInterface : public SensorSingleValue {
 public:
  TemperatureInterface() = delete;
  ~TemperatureInterface() = default;

  explicit TemperatureInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorSingleValue(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif