#ifndef SRC_I2C_STATUS_HPP_
#define SRC_I2C_STATUS_HPP_

namespace i2c {

/**
   * @brief Status of I2C Interface
   * 
   */
enum class I2CStatus : int {
  /// I2C transaction was successful
  I2C_TRANSACTION_SUCCESSFUL,
  /// I2C transaction has failed
  I2C_TRANSACTION_FAILED,
  /// A timeout appeared during I2C transaction
  I2C_TRANSACTION_TIMEOUT,
  /// The I2C Interface is busy
  I2C_TRANSACTION_BUSY,
  /// One or more parameters are not valid
  I2C_PARAMETER_ERROR
};

}  // namespace i2c

#endif