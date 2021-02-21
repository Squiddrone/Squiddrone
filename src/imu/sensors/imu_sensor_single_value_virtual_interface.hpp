#ifndef SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_INTERFACE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_SINGLE_VALUE_INTERFACE_HPP_

#include "imu_sensor_general.hpp"

namespace imu {

class InertialMeasurementSensorSingleValueInterface : public InertialMeasurementSensor {
 public:
  virtual ~InertialMeasurementSensorSingleValueInterface() = default;

  explicit InertialMeasurementSensorSingleValueInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(i2c_handler){};
  virtual auto Get(void) noexcept -> std::int16_t = 0;
};

}  // namespace imu

#endif