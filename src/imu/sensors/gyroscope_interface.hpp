#ifndef SRC_GYROSCOPE_INTERFACE_HPP_
#define SRC_GYROSCOPE_INTERFACE_HPP_

#include "sensor_with_sensitivity.hpp"

namespace imu {

class GyroscopeInterface : public SensorWithSensitivity {
 public:
  GyroscopeInterface() = delete;
  ~GyroscopeInterface() = default;

  explicit GyroscopeInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorWithSensitivity(i2c_handler){};
};

}  // namespace imu

#endif