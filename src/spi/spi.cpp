#include "spi.hpp"

namespace spi {
auto SPI::Transfer(std::vector<uint8_t> &mosi_data_buffer, std::vector<uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  types::DriverStatus return_value = types::DriverStatus::HAL_ERROR;

  if (IsMisoBufferTooSmall(mosi_data_buffer, miso_data_buffer)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  uint8_t transaction_length = static_cast<uint8_t>(miso_data_buffer.size());

  if (IsTransactionLengthExceedingLimits(transaction_length)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  SetChipSelectPin(PinSetting::HIGH);

  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       reinterpret_cast<uint8_t *>(mosi_data_buffer.data()),
                                                       reinterpret_cast<uint8_t *>(miso_data_buffer.data()),
                                                       transaction_length,
                                                       types::SPI_HAL_TX_RX_TIMEOUT);

  SetChipSelectPin(PinSetting::LOW);

  if (transmit_receive_ret_value == HAL_OK) {
    return_value = types::DriverStatus::OK;
  }
  if (transmit_receive_ret_value == HAL_TIMEOUT) {
    return_value = types::DriverStatus::TIMEOUT;
  }
  if (transmit_receive_ret_value == HAL_ERROR) {
    return_value = types::DriverStatus::HAL_ERROR;
  }
  return return_value;
}

auto SPI::IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool {
  return transaction_length > types::SPI_TRANSACTION_LENGTH_LIMIT;
}

auto SPI::IsMisoBufferTooSmall(std::vector<uint8_t> &mosi_buffer, std::vector<uint8_t> &miso_buffer) noexcept -> bool {
  return miso_buffer.size() < mosi_buffer.size();
}

auto SPI::SetChipSelectPin(PinSetting pin_setting) noexcept -> void {
  GPIO_PinState pin_state_active = GPIO_PIN_RESET;
  GPIO_PinState pin_state_inactive = GPIO_PIN_RESET;
  GPIO_PinState pin_state = GPIO_PIN_RESET;

  if (chip_select_.active_state == CSActiveState::ACTIVE_HIGH) {
    pin_state_active = GPIO_PIN_SET;
  } else {
    pin_state_inactive = GPIO_PIN_SET;
  }

  if (pin_setting == PinSetting::ACTIVE) {
    pin_state = pin_state_active;
  } else {
    pin_state = pin_state_inactive;
  }

  HAL_GPIO_WritePin(chip_select_.peripheral, chip_select_.gpio_pin, pin_state);
}

}  // namespace spi
