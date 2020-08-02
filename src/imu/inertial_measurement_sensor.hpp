#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "mpu9255_data.hpp"

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
  auto Mpu9255Detected(void) noexcept -> bool;
  auto Read(std::uint16_t byte_size) noexcept -> std::pair<types::HalError, std::vector<std::uint8_t>>;
  auto Write(const std::vector<std::uint8_t>& data) noexcept -> types::HalError;
  auto ImuConnectionSuccessful(types::HalError imu_status) noexcept -> bool;
  /// Holds the local reference to euclidean sensor values
  types::EuclideanVector<float> sensor_values_{-1, -1, -1};
  /// Holds the local reference to i2c handler
  std::unique_ptr<i2c::I2C> i2c_handler_;
  /// Holds value if Sensor was initialized correctly or not
  bool initialized_ = false;
  /// I2C Address of specific sensor
  std::uint8_t i2c_address_ = 0;
};

}  // namespace imu

#endif