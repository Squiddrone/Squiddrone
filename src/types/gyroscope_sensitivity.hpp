#ifndef SRC_TYPES_GYROSCOPE_SENSITIVITY_HPP_
#define SRC_TYPES_GYROSCOPE_SENSITIVITY_HPP_

namespace types {

/**
 * @brief A enum for Gyroscope Sensitivity of Inertial Measurement Unit
 * 
 */
enum class GyroscopeSensitivity : int {
  /// Finest sensitivity. For MPU9250: Full-Scale Range of +- 250 °/s with a Sensitivity of 131 °/s
  FINEST,
  /// Finer sensitivity. For MPU9250: Full-Scale Range of +- 500 °/s with a Sensitivity of 65.5 °/s
  FINER,
  /// Rougher sensitivity. For MPU9250: Full-Scale Range of +- 1000 °/s with a Sensitivity of 32.8 °/s
  ROUGHER,
  /// Roughest sensitivity. For MPU9250: Full-Scale Range of +- 2000 °/s with a Sensitivity of 16.4 °/s
  ROUGHEST
};

}  // namespace types

#endif