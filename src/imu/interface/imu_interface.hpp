#ifndef SRC_IMU_INTERFACE_HPP_
#define SRC_IMU_INTERFACE_HPP_

#include "basic_types.hpp"
#include "i2c.hpp"
#include "imu_sensitivity.hpp"
#include "mpu9255.hpp"

namespace imu {

/**
 * @brief The InertialMeasurementInterface provides an interface for the Inertial Measurement Unit.
 * 
 */
class InertialMeasurementInterface {
 public:
  InertialMeasurementInterface() = delete;
  virtual ~InertialMeasurementInterface() = default;

  /**
   * @brief  The custom constructor is the one to be used. 
   * @param  i2c_handler Unique pointer to I2C Handler defined by hal driver 
   * 
   */
  explicit InertialMeasurementInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler, std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) : imu_(std::move(imu)){};

  virtual auto Init(void) noexcept -> types::DriverStatus = 0;
  virtual auto Update(void) noexcept -> types::DriverStatus = 0;
  virtual void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept = 0;
  virtual auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept = 0;
  virtual auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity = 0;
  virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> = 0;
  virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> = 0;
  virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> = 0;
  virtual auto GetTemperature(void) noexcept -> int = 0;
  virtual auto UnitTestSetImuSeam(std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) noexcept -> void = 0;

 protected:
  /// Holds the local reference to generic imu
  std::unique_ptr<imu::GenericInertialMeasurementUnit> imu_;
};

}  // namespace imu

#endif