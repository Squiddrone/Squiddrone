#ifndef SRC_TEMPERATURE_INTERFACE_HPP_
#define SRC_TEMPERATURE_INTERFACE_HPP_

#include "imu_sensor_general.hpp"

namespace imu {

class TemperatureInterface : public InertialMeasurementSensor {
 public:
  TemperatureInterface() = delete;
  ~TemperatureInterface() = default;

  explicit TemperatureInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
  virtual auto Update_(void) noexcept -> types::DriverStatus = 0;
  virtual auto Get_(void) noexcept -> std::int16_t = 0;
};

}  // namespace imu

#endif