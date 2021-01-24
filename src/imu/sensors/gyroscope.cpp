#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus {
  SENSOR_DATA_REGISTER = imu::GYRO_XOUT_H;
  CONFIG_REGISTER = imu::GYRO_CONFIG;

  return InertialMeasurementSensorWithSensitivity::Init(i2c_address);
}

}  // namespace imu