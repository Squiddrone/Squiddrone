#ifndef SRC_SPI_SPI_STATUS_HPP_
#define SRC_SPI_SPI_STATUS_HPP_

namespace spi {
enum class SPIStatus : int {
  ///SPI transaction was successful.
  SPI_TRANSACTION_SUCCESSFUL,
  ///SPI transaction failed.
  SPI_TRANSMISSION_FAILED,
  ///Hal signaled an error.
  SPI_HAL_ERROR
};
}

#endif