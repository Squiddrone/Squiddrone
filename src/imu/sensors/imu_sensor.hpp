#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "imu_sensor_virtual_interface.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensor : public InertialMeasurementSensorInterface {
 public:
  virtual ~InertialMeasurementSensor() = default;

  explicit InertialMeasurementSensor(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorInterface(), i2c_handler_(i2c_handler){};
  auto Get(void) noexcept -> types::EuclideanVector<int16_t> override;
  auto Update(void) noexcept -> types::DriverStatus override;

 protected:
  auto Mpu9255Detected(void) noexcept -> bool;
  auto AK8963Detected(void) noexcept -> bool;
  auto Write(const std::vector<std::uint8_t>& data) noexcept -> void;
  auto ReadContentFromRegister(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto WriteContentIntoRegister(std::uint8_t write_into_register, std::uint8_t register_content) noexcept -> types::DriverStatus;
  auto ImuConnectionSuccessful(void) noexcept -> bool;
  auto ImuConnectionFailed(void) noexcept -> bool;
  auto SetI2CAdress(std::uint8_t i2c_address) noexcept -> void;
  auto ConvertUint8BytesIntoInt16SensorValue(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t;
  auto IsInitialized(void) noexcept -> bool;
  auto SetSensorValues(std::int16_t x, std::int16_t y, std::int16_t z) noexcept -> void;

  types::EuclideanVector<std::int16_t> sensor_values_{-1, -1, -1};
  std::shared_ptr<i2c::I2CInterface> i2c_handler_;
  bool initialized_ = false;
  std::uint8_t i2c_address_ = 0;
  types::DriverStatus imu_status_ = types::DriverStatus::HAL_ERROR;
  std::uint8_t SENSOR_DATA_REGISTER = 0;
  std::uint8_t CONFIG_REGISTER = 0;
};

}  // namespace imu

#endif