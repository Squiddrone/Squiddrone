#ifndef SRC_sensor_with_sensitivity_INTERFACE_HPP_
#define SRC_sensor_with_sensitivity_INTERFACE_HPP_

#include "imu_sensitivity.hpp"
#include "mpu9255_data.hpp"
#include "sensor_vector.hpp"

namespace imu {

class SensorWithSensitivityInterface : public SensorVector {
 public:
  SensorWithSensitivityInterface() = delete;
  ~SensorWithSensitivityInterface() = default;

  explicit SensorWithSensitivityInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorVector(i2c_handler){};

  virtual auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
  virtual auto GetSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto SetSensitivity(types::ImuSensitivity sensitivity) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif