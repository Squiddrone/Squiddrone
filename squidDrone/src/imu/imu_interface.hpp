#ifndef SRC_IMU_INTERFACE_HPP_
#define SRC_IMU_INTERFACE_HPP_

#include "i2c_handler.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "accelerometer_sensitivity.hpp"
#include "mpu9250.hpp"

namespace imu {

  ///
  /// @class InertialMeasurementInterface 
  /// @brief The InertialMeasurementInterface provides an interface for the Inertial Measurement Unit.
  ///
  class InertialMeasurementInterface {
    public:
      ///
      /// @brief  Default constructor may not be used, so it is deleted.
      ///
      InertialMeasurementInterface() = delete;

      ///
      /// @brief The default destructor is sufficent
      ///
      virtual ~InertialMeasurementInterface() = default;

      ///
      /// @brief  The custom constructor is the one to be used. 
      /// @param  i2c_handler Unique pointer to I2C Handler defined by hal driver 
      ///
      explicit InertialMeasurementInterface(std::unique_ptr<i2c::I2CHandler> i2c_handler): mpu9250_(std::make_unique<imu::Mpu9250>(std::move(i2c_handler))){};
      
      ///
      /// @brief Used for setting of the gyroscopes sensitivity
      ///
      virtual void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept = 0;

      ///
      /// @brief Used for reading the gyroscopes sensitivity
      /// @return Gyroscopes sensitivity as types::GyroscopeSensitivity
      ///
      virtual auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity = 0;

      ///
      /// @brief Used for setting of the accelerometers sensitivity
      ///
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept = 0;

      ///
      /// @brief Used for reading the accelerometers sensitivity
      /// @return accelerometers sensitivity as types::AccelerometerSensitivity
      ///
      virtual auto GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity = 0;

      ///
      /// @brief Used for reading the gyroscopes measured values
      /// @return Vector of X, Y and Z axis of the orientation in three-dimensional space
      ///
      virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;

      ///
      /// @brief Used for reading the accelerometers measured values
      /// @return Vector of X, Y and Z axis of the acceleration in three-dimensional space
      ///
      virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;

      ///
      /// @brief Used for reading the magnetometers measured values
      /// @return Vector of X, Y and Z axis of the magnetic field in three-dimensional space
      ///
      virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;

      ///
      /// @brief Used for reading the temperature of the Inertial Measurement Unit
      /// @return Temperature of Inertial Measurement Unit as Integer
      ///
      virtual auto GetTemperature(void) noexcept -> int = 0;
    protected:
      /// Holds the local reference to MPU9250
      std::unique_ptr<imu::GenericInertialMeasurementUnit> mpu9250_;
  };

} // namespace imu

#endif