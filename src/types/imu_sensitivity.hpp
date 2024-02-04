#ifndef SRC_TYPES_SENSITIVITY_HPP_
#define SRC_TYPES_SENSITIVITY_HPP_

namespace types {

/**
 * @brief A enum for Sensitivity of Inertial Measurement Unit
 *
 */
enum class ImuSensitivity : int {
  FINEST,
  FINER,
  ROUGHER,
  ROUGHEST
};

}  // namespace types

#endif