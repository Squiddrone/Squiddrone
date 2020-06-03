#include "i2c.hpp"

namespace i2c
{

  auto I2C::Read(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout) noexcept -> std::tuple<I2CStatus, std::vector<std::uint8_t>> {
    I2CStatus i2c_status;

    if (!CheckForValidInputRead(address, byte_size, timeout)) {
      std::vector<std::uint8_t> data;
      i2c_status = I2CStatus::I2C_PARAMETER_ERROR;
      return {i2c_status, data};
    }

    address = ModifyAddressForI2C7Bit(address);

    std::uint8_t buffer[byte_size];
    HAL_StatusTypeDef hal_status = HAL_I2C_Master_Receive(&hi2c2, address, buffer, byte_size, timeout);

    std::vector<std::uint8_t> data(buffer, buffer+byte_size);
    i2c_status = GetI2CStatus(hal_status);

    return {i2c_status, data};
  }

  auto I2C::Write(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout) noexcept -> I2CStatus {
    if (!CheckForValidInputWrite(address, data, timeout)) {
      return I2CStatus::I2C_PARAMETER_ERROR;
    }

    address = ModifyAddressForI2C7Bit(address);

    HAL_StatusTypeDef hal_status = HAL_I2C_Master_Transmit(&hi2c2, address, (std::uint8_t*)data.data(), (std::uint16_t)data.size(), timeout);

    return GetI2CStatus(hal_status);;
  }

  auto I2C::ModifyAddressForI2C7Bit(std::uint8_t address) noexcept -> std::uint8_t {
    //because of 7 Bit addresses in I2C, one shift to the left
    return static_cast<std::uint8_t>(address << 1);
  }

  auto I2C::CheckForValidInputRead(std::uint8_t address, std::uint16_t byte_size, std::uint32_t timeout) noexcept -> bool {
    return CheckIfI2CAddressIsValid(address) && 
      CheckIfI2CAmountOfBytesIsValid(byte_size) && 
      CheckIfI2CTimeoutIsValid(timeout);
  }

  auto I2C::GetI2CStatus(HAL_StatusTypeDef hal_status) noexcept -> I2CStatus
  {
    I2CStatus i2c_status;

    switch (hal_status)
    {
    case HAL_OK:
      i2c_status = I2CStatus::I2C_TRANSACTION_SUCCESSFUL;
      break;
    case HAL_TIMEOUT:
      i2c_status = I2CStatus::I2C_TRANSACTION_TIMEOUT;
      break;
    case HAL_BUSY:
      i2c_status = I2CStatus::I2C_TRANSACTION_BUSY;
      break;
    default:
      i2c_status = I2CStatus::I2C_TRANSACTION_FAILED;
      break;
    }

    return i2c_status;
  }

  auto I2C::CheckForValidInputWrite(std::uint8_t address, const std::vector<std::uint8_t>& data, std::uint32_t timeout) noexcept -> bool {
    return CheckIfI2CAddressIsValid(address) && 
      CheckIfI2CAmountOfBytesIsValid(static_cast<std::uint16_t>(data.size())) && 
      CheckIfI2CTimeoutIsValid(timeout);
  }

  auto I2C::CheckIfI2CAddressIsValid(std::uint8_t address) noexcept -> bool {
    constexpr std::uint8_t i2c_minimum_allowed_7bit_address = 0x08;
    constexpr std::uint8_t i2c_maximum_allowed_7bit_address = 0x77;

    return (address >= i2c_minimum_allowed_7bit_address && address <= i2c_maximum_allowed_7bit_address);
  }

  auto I2C::CheckIfI2CAmountOfBytesIsValid(std::uint16_t amount_of_bytes) noexcept -> bool {
    constexpr std::uint8_t i2c_maximum_allowed_data_size_in_bytes = 32;
    return (amount_of_bytes > 0 && amount_of_bytes <= i2c_maximum_allowed_data_size_in_bytes);
  }

  auto I2C::CheckIfI2CTimeoutIsValid(std::uint32_t timeout) noexcept -> bool {
    return (timeout > 0 && timeout < HAL_MAX_DELAY);
  }
} // namespace i2c
 