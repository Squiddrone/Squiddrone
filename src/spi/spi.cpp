#include "spi.hpp"
#include "stm32g4xx_hal.h"
//preserve include order
#include "spi_config.h"

namespace spi {
auto SPI::Transfer(std::vector<uint8_t> &RxData, std::vector<uint8_t> &TxData) noexcept -> spi::SPIStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  uint16_t transmit_size = TxData.size();
  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       TxData.data(),
                                                       RxData.data(),
                                                       transmit_size,
                                                       0);
}
}  // namespace spi