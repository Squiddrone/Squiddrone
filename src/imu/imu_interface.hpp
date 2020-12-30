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
  /**
   * @brief  Default constructor may not be used, so it is deleted.
   * 
   */
  InertialMeasurementInterface() = delete;

  /**
   * @brief The default destructor is sufficent
   *
   */
  virtual ~InertialMeasurementInterface() = default;

  /**
   * @brief  The custom constructor is the one to be used. 
   * @param  i2c_handler Unique pointer to I2C Handler defined by hal driver 
   * 
   */
  explicit InertialMeasurementInterface(std::shared_ptr<i2c::I2CInterface> i2c_handler, std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) : imu_(std::move(imu)){};

  /**
   * @brief Used for Initialization of complete Inertial Measurement Unit
   * 
   */
  virtual auto Init(void) noexcept -> types::DriverStatus = 0;

  /**
   * @brief Used for setting of the gyroscopes sensitivity
   * 
   */
  virtual void SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept = 0;

  /**
   * @brief Used for reading the gyroscopes sensitivity
   * @return Gyroscopes sensitivity as types::ImuSensitivity
   * 
   */
  virtual auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity = 0;

  /**
   * @brief Used for setting of the accelerometers sensitivity
   * 
   */
  virtual void SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept = 0;

  /**
   * @brief Used for reading the accelerometers sensitivity
   * @return accelerometers sensitivity as types::ImuSensitivity
   * 
   */
  virtual auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity = 0;

  /**
   * @brief Used for reading the gyroscopes measured values
   * @return Vector of X, Y and Z axis of the orientation in three-dimensional space
   * 
   */
  virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;

  /**
   * @brief Used for reading the accelerometers measured values
   * @return Vector of X, Y and Z axis of the acceleration in three-dimensional space
   * 
   */
  virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;

  /**
   * @brief Used for reading the magnetometers measured values
   * @return Vector of X, Y and Z axis of the magnetic field in three-dimensional space
   * 
   */
  virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;

  /**
   * @brief Used for reading the temperature of the Inertial Measurement Unit
   * @return Temperature of Inertial Measurement Unit as Integer
   * 
   */
  virtual auto GetTemperature(void) noexcept -> int = 0;

  /**
  * @brief Only used for Unittests, to be able to inject a Mock Object
  * 
  * @param imu Unique Pointer to Mock Object
  */
  virtual auto UnitTestSetImuSeam(std::unique_ptr<imu::GenericInertialMeasurementUnit> imu) noexcept -> void = 0;

 protected:
  /// Holds the local reference to generic imu
  std::unique_ptr<imu::GenericInertialMeasurementUnit> imu_;
};

}  // namespace imu

#endif