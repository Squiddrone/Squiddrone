#include "magnetometer.hpp"

namespace imu {

auto Magnetometer::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::MAGNETOMETER_XOUT_L;
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!AK8963Detected())
    return types::DriverStatus::HAL_ERROR;

  SetSensorValues(0, 0, 0);

  if (ImuConnectionFailed())
    return types::DriverStatus::HAL_ERROR;

  initialized_ = true;
  return types::DriverStatus::OK;
}

}  // namespace imu