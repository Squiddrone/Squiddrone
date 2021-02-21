#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "imu_sensor_general_virtual_interface.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensor : public InertialMeasurementSensorGeneralInterface {
 public:
  virtual ~InertialMeasurementSensor() = default;

  explicit InertialMeasurementSensor(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorGeneralInterface(), i2c_handler_(i2c_handler){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;

 protected:
  auto Mpu9255Detected(void) noexcept -> bool;
  auto AK8963Detected(void) noexcept -> bool;
  auto ReadContentFromRegister(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto WriteContentIntoRegister(std::uint8_t write_into_register, std::uint8_t register_content) noexcept -> void;
  auto ImuConnectionSuccessful(void) noexcept -> bool;
  auto ImuConnectionFailed(void) noexcept -> bool;
  auto SetI2CAdress(std::uint8_t i2c_address) noexcept -> void;
  auto ConvertUint8BytesIntoInt16SensorValue(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t;
  auto IsInitialized(void) noexcept -> bool;

  std::shared_ptr<i2c::I2CInterface> i2c_handler_;
  bool initialized_ = false;
  std::uint8_t i2c_address_ = 0;
  types::DriverStatus imu_status_ = types::DriverStatus::HAL_ERROR;
  std::vector<uint8_t> raw_values_;
  std::uint8_t SENSOR_DATA_REGISTER = 0;
  std::uint8_t REGISTER_DATA_LENGTH_IN_BYTES = 0;
  std::uint8_t CONFIG_REGISTER = 0;
};

}  // namespace imu

#endif