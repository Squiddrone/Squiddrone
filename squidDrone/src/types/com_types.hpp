#ifndef SRC_TYPES_COM_TYPES_HPP_
#define SRC_TYPES_COM_TYPES_HPP_

#include <cstdint>

namespace types {
  /**
   * @brief Enum class to contain error codes for COM module.
   * 
   */
  enum class ComError: std::int8_t {
      /// No error
      COM_OK,
      /// Buffer overflow error
      COM_BUFFER_OVERFLOW,
      /// Buffer IO error i.e. faulty data in buffer
      COM_BUFFER_IO_ERROR
  };

  // Fixed length for com message frames.
  const std::uint8_t max_frame_length = 32;
}

#endif