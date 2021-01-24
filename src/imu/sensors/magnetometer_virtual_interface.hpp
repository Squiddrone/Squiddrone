#ifndef SRC_MAGNETOMETER_INTERFACE_HPP_
#define SRC_MAGNETOMETER_INTERFACE_HPP_

#include "imu_sensor.hpp"

namespace imu {

class MagnetometerInterface : public InertialMeasurementSensor {
 public:
  MagnetometerInterface() = delete;
  ~MagnetometerInterface() = default;

  explicit MagnetometerInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif