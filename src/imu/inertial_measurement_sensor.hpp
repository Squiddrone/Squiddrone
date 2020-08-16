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
  auto Get(void) noexcept -> types::EuclideanVector<int16_t>;

 protected:
  auto Mpu9255Detected(void) noexcept -> bool;
  auto Read(std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto Write(const std::vector<std::uint8_t>& data) noexcept -> void;
  auto ReadDataBytes(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto ImuConnectionSuccessful(void) noexcept -> bool;
  auto SetI2CAdress(std::uint8_t i2c_address) noexcept -> void;
  auto ConvertUint8BytesIntoInt16SensorValue(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t;

  /// Holds the local reference to euclidean sensor values
  types::EuclideanVector<int16_t> sensor_values_{-1, -1, -1};
  /// Holds the local reference to i2c handler
  std::unique_ptr<i2c::I2C> i2c_handler_;
  /// Holds value if Sensor was initialized correctly or not
  bool initialized_ = false;
  /// I2C Address of specific sensor
  std::uint8_t i2c_address_ = 0;
  /// Status of last communication action of IMU sensor
  types::HalError imu_status_ = types::HalError::CONFIG_ERROR;
};

}  // namespace imu

#endif