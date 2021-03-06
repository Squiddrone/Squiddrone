#ifndef SRC_TYPES_COM_TYPES_HPP_
#define SRC_TYPES_COM_TYPES_HPP_

#include <cstdint>
#include <vector>

namespace types {
/**
 * @brief Enum class to contain error codes for COM module.
 * 
 */
enum class ComError : std::int8_t {
  /// No error
  COM_OK,
  /// Buffer overflow error
  COM_BUFFER_OVERFLOW,
  /// Buffer IO error i.e. faulty data in buffer
  COM_BUFFER_IO_ERROR
};

/// Max depth for the com buffer.
static constexpr std::uint8_t COM_BUFFER_MAX_QUEUE_LENGTH = 5;

/// Max length for com message frames.
static constexpr std::uint8_t COM_MAX_FRAME_LENGTH = 32;

/// Type alias for com message frame datatype
using com_msg_frame = std::vector<std::uint8_t>;
}  // namespace types

#endif