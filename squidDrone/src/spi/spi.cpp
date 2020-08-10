#include "spi.hpp"

namespace spi {
auto SPI::Transfer(std::unique_ptr<std::uint8_t> RxData,
              std::unique_ptr<std::uint8_t> TxData) noexcept -> spi::SPIStatus {
  return spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
}
}