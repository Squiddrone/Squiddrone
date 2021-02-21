#ifndef SRC_IMU_MEASUREMENT_SENSOR_INTERFACE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_INTERFACE_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensorGeneralInterface {
 public:
  virtual ~InertialMeasurementSensorGeneralInterface() = default;

  explicit InertialMeasurementSensorGeneralInterface(void){};
  virtual auto Get(void) noexcept -> types::EuclideanVector<int16_t> = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif