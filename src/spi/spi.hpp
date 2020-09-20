#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include "spi_interface.hpp"

namespace spi {

class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(const std::uint16_t chip_select) : spi::SPIInterface(), chip_select_(chip_select){};
  virtual ~SPI() = default;

  auto Transfer(std::vector<uint8_t> &miso_data_buffer, std::vector<uint8_t> &mosi_data_buffer) noexcept -> spi::SPIStatus override;

 private:
  std::uint16_t chip_select_;
};

}  // namespace spi

#endif