#ifndef SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_HPP_

#include "sensor_single_value_virtual_interface.hpp"

namespace imu {

class SensorSingleValue : public SensorSingleValueInterface {
 public:
  virtual ~SensorSingleValue() = default;

  explicit SensorSingleValue(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorSingleValueInterface(i2c_handler){};
  auto Update(void) noexcept -> types::DriverStatus override;
  auto Get(void) noexcept -> std::int16_t override;

 protected:
  auto SetSensorValue(const std::int16_t new_value) noexcept -> void;

  std::int16_t sensor_value_ = -1;
};

}  // namespace imu

#endif