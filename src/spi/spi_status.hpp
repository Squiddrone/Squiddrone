#ifndef SRC_SPI_SPI_STATUS_HPP_
#define SRC_SPI_SPI_STATUS_HPP_

namespace spi {
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
}

#endif