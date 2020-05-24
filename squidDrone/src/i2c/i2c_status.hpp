#ifndef SRC_I2C_STATUS_HPP_
#define SRC_I2C_STATUS_HPP_

namespace i2c {

  enum class I2CStatus: int{
    I2C_TRANSACTION_SUCCESSFUL,
    I2C_TRANSACTION_FAILED,
    I2C_TRANSACTION_TIMEOUT,
    I2C_TRANSACTION_BUSY
  };

} // namespace i2c

#endif