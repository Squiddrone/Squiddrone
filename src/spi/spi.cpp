#include "spi.hpp"
#include "stm32g4xx.h"
//preserve include order
#include "spi_config.h"

namespace spi {
auto SPI::Transfer(std::vector<uint8_t> &RxData, std::vector<uint8_t> &TxData) noexcept -> spi::SPIStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  spi::SPIStatus return_value = spi::SPIStatus::SPI_HAL_ERROR;
  uint16_t transmit_size = static_cast<uint16_t>(TxData.size());
  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       TxData.data(),
                                                       RxData.data(),
                                                       transmit_size,
                                                       0);
  if (transmit_receive_ret_value == HAL_OK) {
    return_value = spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
  }
  if (transmit_receive_ret_value == HAL_TIMEOUT) {
    return_value = spi::SPIStatus::SPI_TRANSMISSION_FAILED;
  }
  if (transmit_receive_ret_value == HAL_ERROR) {
    return_value = spi::SPIStatus::SPI_HAL_ERROR;
  }
  return return_value;
}
}  // namespace spi