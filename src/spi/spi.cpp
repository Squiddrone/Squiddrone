#include "spi.hpp"
#include <spi_types.hpp>

#include <array>
#include "stm32g4xx.h"

//preserve include order
#include "spi_config.h"

namespace spi {
auto SPI::Transfer(std::vector<uint8_t> &miso_data_buffer, std::vector<uint8_t> &mosi_data_buffer) noexcept -> spi::SPIStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  spi::SPIStatus return_value = spi::SPIStatus::SPI_HAL_ERROR;

  uint16_t transmit_size = static_cast<uint16_t>(mosi_data_buffer.size());

  if (IsBufferSizeExceedingLimits(transmit_size)) {
    return spi::SPIStatus::SPI_BUFFER_SIZE_LIMIT_EXCEEDED;
  }

  miso_data_buffer.resize(transmit_size);

  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       reinterpret_cast<uint8_t *>(mosi_data_buffer.data()),
                                                       reinterpret_cast<uint8_t *>(miso_data_buffer.data()),
                                                       transmit_size,
                                                       SPI_HAL_TX_RX_TIMEOUT);
  if (transmit_receive_ret_value == HAL_OK) {
    return_value = spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
  }
  if (transmit_receive_ret_value == HAL_TIMEOUT) {
    return_value = spi::SPIStatus::SPI_TRANSACTION_FAILED;
  }
  if (transmit_receive_ret_value == HAL_ERROR) {
    return_value = spi::SPIStatus::SPI_HAL_ERROR;
  }
  return return_value;
}

auto SPI::IsBufferSizeExceedingLimits(std::uint16_t buffer_size) -> bool {
  bool return_value = false;
  if (buffer_size > SPI_MISO_BUFFER_SIZE) {
    return_value = true;
  }
  return return_value;
}

}  // namespace spi
