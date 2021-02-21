#ifndef SRC_IMU_SENSOR_WITH_SENSITIVITY_HPP_
#define SRC_IMU_SENSOR_WITH_SENSITIVITY_HPP_

#include "imu_sensitivity.hpp"
#include "imu_sensor_general.hpp"
#include "imu_sensor_with_sensitivity.hpp"
#include "imu_sensor_with_sensitivity_virtual_interface.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensorWithSensitivity : public InertialMeasurementSensorWithSensitivityInterface {
 public:
  InertialMeasurementSensorWithSensitivity() = delete;
  ~InertialMeasurementSensorWithSensitivity() = default;

  explicit InertialMeasurementSensorWithSensitivity(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensorWithSensitivityInterface(i2c_handler){};

  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto GetSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus override;

 protected:
  auto GetConfigRegisterDataForSensitivity(types::ImuSensitivity sensitivity) noexcept -> std::uint8_t;
  auto SendSensitivityRegisterData(types::ImuSensitivity sensitivity) noexcept -> void;
  auto SaveNewSensitivity(types::ImuSensitivity sensitivity) noexcept -> void;

  types::ImuSensitivity sensitivity_ = types::ImuSensitivity::FINEST;
};

}  // namespace imu

#endif