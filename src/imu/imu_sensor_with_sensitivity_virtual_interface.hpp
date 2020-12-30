#ifndef SRC_IMU_SENSOR_WITH_SENSITIVITY_INTERFACE_HPP_
#define SRC_IMU_SENSOR_WITH_SENSITIVITY_INTERFACE_HPP_

#include "imu_sensitivity.hpp"
#include "imu_sensor.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensorWithSensitivityInterface : public InertialMeasurementSensor {
 public:
  InertialMeasurementSensorWithSensitivityInterface() = delete;
  ~InertialMeasurementSensorWithSensitivityInterface() = default;

  explicit InertialMeasurementSensorWithSensitivityInterface(std::unique_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(std::move(i2c_handler)){};

  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
  virtual auto GetSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif