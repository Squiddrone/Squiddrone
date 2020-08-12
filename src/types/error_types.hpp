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

}  // namespace types

#endif