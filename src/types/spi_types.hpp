#ifndef SRC_SPI_SPI_TYPES_HPP_
#define SRC_SPI_SPI_TYPES_HPP_

#include <cinttypes>

namespace types {
/**
 * @brief Enum class of type inf for spi status return values.
 * 
 */
enum class SPIStatus : int {
  ///SPI transaction was successful.
  SPI_TRANSACTION_SUCCESSFUL,
  ///SPI transaction failed.
  SPI_TRANSACTION_FAILED,
  ///Hal signaled an error.
  SPI_HAL_ERROR,
  ///Data buffer size exceeding limit
  SPI_BUFFER_SIZE_LIMIT_EXCEEDED
};
}  // namespace types

#endif