#ifndef SRC_TYPES_ERROR_TYPES_HPP_
#define SRC_TYPES_ERROR_TYPES_HPP_

#include <cstdint>

namespace types{

  ///
  /// @brief A error type enum
  ///
  enum class HalError: std::uint16_t{
    /// Hal function is working
    working,
    /// Configuration returned an error
    config_error,
    /// parameter change failed
    parameter_change_error
  };

}

#endif 