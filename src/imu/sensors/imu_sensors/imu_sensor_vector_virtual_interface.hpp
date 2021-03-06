#ifndef SRC_IMU_MEASUREMENT_SENSOR_VECTOR_INTERFACE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_VECTOR_INTERFACE_HPP_

#include "imu_sensor_general.hpp"

namespace imu {

class SensorVectorInterface : public SensorGeneral {
 public:
  virtual ~SensorVectorInterface() = default;

  explicit SensorVectorInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorGeneral(i2c_handler){};
  virtual auto Get(void) noexcept -> types::EuclideanVector<int16_t> = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif