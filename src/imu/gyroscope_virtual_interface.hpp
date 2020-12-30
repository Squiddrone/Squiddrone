#ifndef SRC_GYROSCOPE_INTERFACE_HPP_
#define SRC_GYROSCOPE_INTERFACE_HPP_

#include "imu_sensor_with_sensitivity.hpp"

namespace imu {

class GyroscopeInterface : public InertialMeasurementSensorWithSensitivity {
 public:
  GyroscopeInterface() = delete;
  ~GyroscopeInterface() = default;

  explicit GyroscopeInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorWithSensitivity(i2c_handler){};
  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif