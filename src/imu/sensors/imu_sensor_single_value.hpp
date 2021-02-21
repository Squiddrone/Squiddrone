#ifndef SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_HPP_

#include "imu_sensor_single_value_virtual_interface.hpp"

namespace imu {

class InertialMeasurementSensorSingleValue : public InertialMeasurementSensorSingleValueInterface {
 public:
  virtual ~InertialMeasurementSensorSingleValue() = default;

  explicit InertialMeasurementSensorSingleValue(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorSingleValueInterface(i2c_handler){};
  auto Update(void) noexcept -> types::DriverStatus override;
  auto Get(void) noexcept -> std::int16_t override;

 protected:
  auto SetSensorValue(std::int16_t new_value) noexcept -> void;

  std::int16_t sensor_value_ = -1;
};

}  // namespace imu

#endif