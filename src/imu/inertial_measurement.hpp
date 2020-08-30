#ifndef SRC_INERTIAL_MEASUREMENT_HPP_
#define SRC_INERTIAL_MEASUREMENT_HPP_

#include "imu_interface.hpp"

namespace imu {

/**
 * @brief Concrete implementation of the Inertial Measurement Unit Interface.
 * 
 */
class InertialMeasurement final : public InertialMeasurementInterface {
 public:
  InertialMeasurement() = delete;
  ~InertialMeasurement() = default;

  /**
   * @brief  The custom constructor is
   *          the one to be used. 
   * @param  i2c_handler Unique pointer to I2C Handler defined by hal driver 
   * 
   */
  explicit InertialMeasurement(std::unique_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementInterface(std::move(i2c_handler), std::make_unique<imu::Mpu9255>(std::move(i2c_handler))) {}
  void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept override;
  auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity override;
  void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept override;
  auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> override;
  auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> override;
  auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> override;
  auto GetTemperature(void) noexcept -> int override;
  auto SetImuSeam(std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) noexcept -> void override;
};

}  // namespace imu

#endif