#include "spi.hpp"

auto Transfer(std::unique_ptr<std::uint8_t> RxData,
              std::unique_ptr<std::uint8_t> TxData) noexcept -> spi::SPIStatus {
  return spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
}