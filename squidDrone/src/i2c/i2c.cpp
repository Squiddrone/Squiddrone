#include "i2c.hpp"

namespace i2c
{

  auto I2C::read(uint8_t address, uint16_t byte_size, uint32_t timeout) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> {
    I2CStatus i2c_status;

    if (!check_for_valid_input_read(address, byte_size, timeout)) {
      std::vector<uint8_t> data;
      i2c_status = I2CStatus::I2C_PARAMETER_ERROR;
      return {i2c_status, data};
    }

    address = modify_address_for_i2c_7bit(address);

    uint8_t buffer[byte_size];
    HAL_StatusTypeDef hal_status = HAL_I2C_Master_Receive(&hi2c2, address, buffer, byte_size, timeout);

    std::vector<uint8_t> data(buffer, buffer+byte_size);
    i2c_status = get_i2c_status(hal_status);

    return {i2c_status, data};
  }

  auto I2C::write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout) noexcept -> I2CStatus {
    if (!check_for_valid_input_write(address, data, timeout)) {
      return I2CStatus::I2C_PARAMETER_ERROR;
    }

    address = modify_address_for_i2c_7bit(address);

    HAL_StatusTypeDef hal_status = HAL_I2C_Master_Transmit(&hi2c2, address, (uint8_t*)data.data(), (uint16_t)data.size(), timeout);

    return get_i2c_status(hal_status);;
  }

  auto I2C::modify_address_for_i2c_7bit(uint8_t address) noexcept -> uint8_t {
    //because of 7 Bit addresses in I2C, one shift to the left
    return (uint8_t)(address << 1);
  }

  auto I2C::check_for_valid_input_read(uint8_t address, uint16_t byte_size, uint32_t timeout) noexcept -> bool {
    return check_if_i2c_address_is_valid(address) && 
      check_if_i2c_amount_of_bytes_is_valid(byte_size) && 
      check_if_i2c_timeout_is_valid(timeout);
  }

  auto I2C::get_i2c_status(HAL_StatusTypeDef hal_status) noexcept -> I2CStatus {
    I2CStatus i2c_status;

    if (hal_status == HAL_OK) {
        i2c_status = I2CStatus::I2C_TRANSACTION_SUCCESSFUL;
      }
    else if (hal_status == HAL_ERROR) {
        i2c_status = I2CStatus::I2C_TRANSACTION_FAILED;
      }
    else if (hal_status == HAL_TIMEOUT) {
        i2c_status = I2CStatus::I2C_TRANSACTION_TIMEOUT;
      }
    else if (hal_status == HAL_BUSY) {
        i2c_status = I2CStatus::I2C_TRANSACTION_BUSY;
      }
    else {
      i2c_status = I2CStatus::I2C_TRANSACTION_FAILED;
    }

    return i2c_status;
  }

  auto I2C::check_for_valid_input_write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout) noexcept -> bool {
    return check_if_i2c_address_is_valid(address) && 
      check_if_i2c_amount_of_bytes_is_valid((uint16_t)data.size()) && 
      check_if_i2c_timeout_is_valid(timeout);
  }

  auto I2C::check_if_i2c_address_is_valid(uint8_t address) noexcept -> bool {
    constexpr uint8_t i2c_minimum_allowed_7bit_address = 0x08;
    constexpr uint8_t i2c_maximum_allowed_7bit_address = 0x77;

    if (address >= i2c_minimum_allowed_7bit_address && address <= i2c_maximum_allowed_7bit_address) {
      return true;
    }
    else {
      return false;
    }
  }

  auto I2C::check_if_i2c_amount_of_bytes_is_valid(uint16_t amount_of_bytes) noexcept -> bool {
    constexpr uint8_t i2c_maximum_allowed_data_size_in_bytes = 32;
    return ((amount_of_bytes > 0 && amount_of_bytes <= i2c_maximum_allowed_data_size_in_bytes) ? true : false);
  }

  auto I2C::check_if_i2c_timeout_is_valid(uint32_t timeout) noexcept -> bool {
    return ((timeout > 0 && timeout < HAL_MAX_DELAY) ? true : false);
  }
} // namespace i2c
 