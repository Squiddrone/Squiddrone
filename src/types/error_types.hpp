#ifndef SRC_TYPES_ERROR_TYPES_HPP_
#define SRC_TYPES_ERROR_TYPES_HPP_

#include <cstdint>

namespace types {

/**
 * @brief The error type for the drivers layer
 *  of the software
 * 
 */
enum class DriverStatus : int {
  OK,
  HAL_ERROR,
  INPUT_ERROR,
  TIMEOUT
};

/**
 * @brief A hardware setup enum to identify hardware setup
 *  errors on abstraction levels above the HAL and 
 *  HAL interfacing classes
 * 
 */
enum class HardwareSetupError : int {
  // Setup worked flawlessly
  HARDWARE_SETUP_CORRECT,
  /// Hardware and/or HAL reports errors
  HARDWARE_REPORTS_ERRORS
};

}  // namespace types

#endif