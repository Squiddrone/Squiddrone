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
  /**
   * @brief  Default constructor may not be used, so it is deleted.
   * 
   */
  InertialMeasurement() = delete;

  /**
   * @brief The default destructor is sufficent
   *
   */
  ~InertialMeasurement() = default;

  /**
   * @brief  The custom constructor is
   *          the one to be used. 
   * @param  i2c_handler Unique pointer to I2C Handler defined by hal driver 
   * 
   */
  explicit InertialMeasurement(std::shared_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementInterface(i2c_handler, std::make_unique<imu::Mpu9255>(i2c_handler)) {}

  /**
   * @brief Used for Initialization of complete Inertial Measurement Unit
   * 
   */
  auto Init(void) noexcept -> types::DriverStatus override;

  /**
   * @brief Used to update all sensors from Inertial Measurement Unit
   * 
   */
  auto Update(void) noexcept -> types::DriverStatus override;

  /**
   * @brief Used for setting of the gyroscopes sensitivity
   * 
   */
  void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept override;

  /**
   * @brief Used for reading the gyroscopes sensitivity
   * @return Gyroscopes sensitivity as types::ImuSensitivity
   * 
   */
  auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity override;

  /**
   * @brief Used for setting of the accelerometers sensitivity
   * 
   */
  void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept override;

  /**
   * @brief Used for reading the accelerometers sensitivity
   * @return accelerometers sensitivity as types::ImuSensitivity
   * 
   */
  auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity override;

  /**
   * @brief Used for reading the gyroscopes measured values
   * @return Vector of X, Y and Z axis of the orientation in three-dimensional space
   * 
   */
  auto GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> override;

  /**
   * @brief Used for reading the accelerometers measured values
   * @return Vector of X, Y and Z axis of the acceleration in three-dimensional space
   * 
   */
  auto GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;

  /**
   * @brief Used for reading the magnetometers measured values
   * @return Vector of X, Y and Z axis of the magnetic field in three-dimensional space
   * 
   */
  auto GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;

  /**
   * @brief Used for reading the temperature of the Inertial Measurement Unit
   * @return Temperature of Inertial Measurement Unit as Integer
   * 
   */
  auto GetTemperature(void) noexcept -> int override;

  /**
  * @brief Only used for Unittests, to be able to inject a Mock Object
  * 
  * @param imu Unique Pointer to Mock Object
  */
  auto UnitTestSetImuSeam(std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) noexcept -> void override;
};

}  // namespace imu

#endif