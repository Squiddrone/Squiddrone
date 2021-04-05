#ifndef SRC_IMU_MEASUREMENT_SENSOR_INTERFACE_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_INTERFACE_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class GeneralSensorInterface {
 public:
  virtual ~GeneralSensorInterface() = default;

  explicit GeneralSensorInterface(void){};
  virtual auto Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus = 0;
  virtual auto GetRawValues(void) noexcept -> types::DriverStatus = 0;
};

}  // namespace imu

#endif