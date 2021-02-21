#ifndef SRC_IMU_MEASUREMENT_SENSOR_VECTOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_VECTOR_HPP_

#include "imu_sensor_vector_virtual_interface.hpp"

namespace imu {

class InertialMeasurementSensorVector : public InertialMeasurementSensorVectorInterface {
 public:
  virtual ~InertialMeasurementSensorVector() = default;

  explicit InertialMeasurementSensorVector(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorVectorInterface(i2c_handler){};
  auto Update(void) noexcept -> types::DriverStatus override;
  auto Get(void) noexcept -> types::EuclideanVector<int16_t> override;

 protected:
  auto SetSensorValues(std::int16_t x, std::int16_t y, std::int16_t z) noexcept -> void;

  types::EuclideanVector<std::int16_t> sensor_values_{-1, -1, -1};
};

}  // namespace imu

#endif