#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"

namespace imu {

class InertialMeasurementSensor {
 public:
  /**
   * @brief The default destructor is sufficent
   */
  virtual ~InertialMeasurementSensor() = default;

  explicit InertialMeasurementSensor(std::unique_ptr<i2c::I2C> i2c_handler) : i2c_handler_(std::move(i2c_handler)){};

  auto Get(void) noexcept -> types::EuclideanVector<float>;
  auto Update(void) noexcept -> types::HalError;

 protected:
  /// Holds the local reference to euclidean sensor values
  std::unique_ptr<types::EuclideanVector<float>> sensor_values_;
  /// Holds the local reference to i2c handler
  std::unique_ptr<i2c::I2C> i2c_handler_;
  /// I2C Address of specific sensor
  uint8_t i2c_address_;
  /// Register of value of specific sensor
  uint8_t register_;
};

}  // namespace imu

#endif