#ifndef SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_INTERFACE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_INTERFACE_HPP_

#include "general.hpp"

namespace imu {

class SensorSingleValueInterface : public GeneralSensor {
 public:
  virtual ~SensorSingleValueInterface() = default;

  explicit SensorSingleValueInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : GeneralSensor(i2c_handler){};
  virtual auto Get(void) noexcept -> std::int16_t = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif