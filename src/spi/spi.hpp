#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include "spi_interface.hpp"

namespace spi {

///Maximum buffer size allowed for SPI Transaction
static constexpr std::uint8_t SPI_TRANSACTION_BUFFER_SIZE_LIMIT = 64;
static constexpr std::uint8_t SPI_HAL_TX_RX_TIMEOUT = 100;

/**
 * @brief Concrete implementation of the SPI interface.
 * 
 */
class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(const std::uint16_t chip_select) : spi::SPIInterface(), chip_select_(chip_select){};
  virtual ~SPI() = default;

  auto Transfer(std::vector<uint8_t> &miso_data_buffer, std::vector<uint8_t> &mosi_data_buffer) noexcept -> spi::SPIStatus override;

 private:
  std::uint16_t chip_select_;

  auto IsBufferSizeExceedingLimits(std::uint16_t buffer_size) -> bool;
};

}  // namespace spi

#endif