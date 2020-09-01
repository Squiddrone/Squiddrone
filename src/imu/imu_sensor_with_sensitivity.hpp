#ifndef SRC_IMU_SENSOR_WITH_SENSITIVITY_HPP_
#define SRC_IMU_SENSOR_WITH_SENSITIVITY_HPP_

#include "imu_sensitivity.hpp"
#include "imu_sensor.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensorWithSensitivity : public InertialMeasurementSensor {
 public:
  InertialMeasurementSensorWithSensitivity() = delete;
  ~InertialMeasurementSensorWithSensitivity() = default;

  explicit InertialMeasurementSensorWithSensitivity(std::unique_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(std::move(i2c_handler)){};

  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus;
  auto GetSensitivity(void) noexcept -> types::ImuSensitivity;
  auto SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus;

 protected:
  auto GetConfigRegisterDataForSensitivity(types::ImuSensitivity sensitivity) noexcept -> std::uint8_t;
  auto SendSensitivityRegisterData(types::ImuSensitivity sensitivity) noexcept -> void;
  auto SaveNewSensitivity(types::ImuSensitivity sensitivity) noexcept -> void;

  types::ImuSensitivity sensitivity_ = types::ImuSensitivity::FINEST;
};

}  // namespace imu

#endif