#include "accelerometer.hpp"

namespace imu {

auto Accelerometer::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::ACCEL_XOUT_H;
  CONFIG_REGISTER = imu::ACCEL_CONFIG;

  return InertialMeasurementSensorWithSensitivity::Init(i2c_address);
}

}  // namespace imu