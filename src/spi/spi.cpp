#include "spi.hpp"

namespace spi {
auto SPI::Write(std::vector<std::uint8_t> &mosi_data_buffer) noexcept -> types::DriverStatus {
  HAL_StatusTypeDef transmit_ret_value = HAL_ERROR;

  std::uint8_t transaction_length = static_cast<std::uint8_t>(mosi_data_buffer.size());

  if (IsTransactionLengthExceedingLimits(transaction_length)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  chip_select_.SetCSActive();

  transmit_ret_value = HAL_SPI_Transmit(&hspi1,
                                        reinterpret_cast<std::uint8_t *>(mosi_data_buffer.data()),
                                        transaction_length,
                                        types::SPI_HAL_TX_RX_TIMEOUT);

  chip_select_.SetCSInactive();

  return CheckHALReturnValue(transmit_ret_value);
}

auto SPI::Transfer(std::vector<std::uint8_t> &mosi_data_buffer, std::vector<std::uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_StatusTypeDef::HAL_ERROR;

  if (IsMisoBufferTooSmall(mosi_data_buffer, miso_data_buffer)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  std::uint8_t transaction_length = static_cast<std::uint8_t>(miso_data_buffer.size());

  if (IsTransactionLengthExceedingLimits(transaction_length)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  chip_select_.SetCSActive();

  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       reinterpret_cast<std::uint8_t *>(mosi_data_buffer.data()),
                                                       reinterpret_cast<std::uint8_t *>(miso_data_buffer.data()),
                                                       transaction_length,
                                                       types::SPI_HAL_TX_RX_TIMEOUT);

  chip_select_.SetCSInactive();

  return CheckHALReturnValue(transmit_receive_ret_value);
}

auto SPI::IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool {
  return transaction_length > types::SPI_TRANSACTION_LENGTH_LIMIT;
}

auto SPI::IsMisoBufferTooSmall(std::vector<std::uint8_t> &mosi_buffer, std::vector<std::uint8_t> &miso_buffer) noexcept -> bool {
  return miso_buffer.size() < mosi_buffer.size();
}

auto SPI::CheckHALReturnValue(HAL_StatusTypeDef hal_return_value) -> types::DriverStatus {
  types::DriverStatus return_value = types::DriverStatus::HAL_ERROR;
  if (hal_return_value == HAL_OK) {
    return_value = types::DriverStatus::OK;
  }
  if (hal_return_value == HAL_TIMEOUT) {
    return_value = types::DriverStatus::TIMEOUT;
  }
  if (hal_return_value == HAL_ERROR) {
    return_value = types::DriverStatus::HAL_ERROR;
  }
  return return_value;
}

}  // namespace spi
