#include "spi.hpp"

namespace spi {
auto SPI::Transfer(std::vector<uint8_t> &miso_data_buffer, std::vector<uint8_t> &mosi_data_buffer) noexcept -> spi::SPIStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  spi::SPIStatus return_value = spi::SPIStatus::SPI_HAL_ERROR;

  uint8_t transmit_size = static_cast<uint8_t>(mosi_data_buffer.size());

  if (IsBufferSizeExceedingLimits(transmit_size)) {
    return spi::SPIStatus::SPI_BUFFER_SIZE_LIMIT_EXCEEDED;
  }

  miso_data_buffer.resize(transmit_size);

  SetChipSelectPin(PinSetting::HIGH);

  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       reinterpret_cast<uint8_t *>(mosi_data_buffer.data()),
                                                       reinterpret_cast<uint8_t *>(miso_data_buffer.data()),
                                                       transmit_size,
                                                       SPI_HAL_TX_RX_TIMEOUT);

  SetChipSelectPin(PinSetting::LOW);

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

auto SPI::IsBufferSizeExceedingLimits(std::uint8_t buffer_size) noexcept -> bool {
  bool return_value = false;
  if (buffer_size > SPI_TRANSACTION_BUFFER_SIZE_LIMIT) {
    return_value = true;
  }
  return return_value;
}

auto SPI::SetChipSelectPin(PinSetting pin_high_or_low) noexcept -> void {
  GPIO_PinState pin_state = GPIO_PIN_RESET;

  switch (pin_high_or_low) {
    case PinSetting::HIGH:
      pin_state = GPIO_PIN_SET;
      break;
    case PinSetting::LOW:
      pin_state = GPIO_PIN_RESET;
      break;
  }

  HAL_GPIO_WritePin(chip_select_.peripheral, chip_select_.gpio_pin, pin_state);
}

}  // namespace spi
