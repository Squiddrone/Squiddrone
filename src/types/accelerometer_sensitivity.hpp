#ifndef SRC_TYPES_ACCELEROMETER_SENSITIVITY_HPP_
#define SRC_TYPES_ACCELEROMETER_SENSITIVITY_HPP_

namespace types{

  /**
   * @brief A enum for Accelerometer Sensitivity of Inertial Measurement Unit
   * 
   */
  enum class AccelerometerSensitivity: int{
    /// Finest sensitivity. For MPU9250: Full-Scale Range of +- 2g with a Sensitivity of 16.384 LSB/g
    FINEST,
    /// Finer sensitivity. For MPU9250: Full-Scale Range of +- 4g with a Sensitivity of 8.192 LSB/g
    FINER,
    /// Rougher sensitivity. For MPU9250: Full-Scale Range of +- 8g with a Sensitivity of 4.096 LSB/g
    ROUGHER,
    /// Roughest sensitivity. For MPU9250: Full-Scale Range of +- 16g with a Sensitivity of 2.048 LSB/g
    ROUGHEST
  };

}

#endif 