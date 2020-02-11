#ifndef SRC_TYPES_ERROR_TYPES_HPP_
#define SRC_TYPES_ERROR_TYPES_HPP_

#include <cstdint>

namespace types{

  ///
  /// @brief A error type enum
  ///
  enum class HalError: std::uint16_t{
    /// Hal function is working
    WORKING,
    /// Configuration returned an error
    CONFIG_ERROR,
    /// parameter failed
    PARAMETER_ERROR
  };

}

#endif 