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

  auto Init(uint8_t i2c_address, uint8_t register_address) noexcept -> types::HalError;
  auto Get(void) noexcept -> types::EuclideanVector<float>;
  auto Update(void) noexcept -> types::HalError;

 protected:
  /// Holds the local reference to euclidean sensor values
  types::EuclideanVector<float> sensor_values_{0, 0, 0};
  /// Holds the local reference to i2c handler
  std::unique_ptr<i2c::I2C> i2c_handler_;
  /// Holds value if Sensor was initialized correctly or not
  bool initialized_ = false;
  /// I2C Address of specific sensor
  uint8_t i2c_address_;
  /// Register of value of specific sensor
  uint8_t register_address_;
};

}  // namespace imu

#endif