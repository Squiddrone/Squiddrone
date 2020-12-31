#ifndef SRC_ACCELEROMETER_HPP_
#define SRC_ACCELEROMETER_HPP_

#include "accelerometer_virtual_interface.hpp"

namespace imu {

class Accelerometer final : public AccelerometerInterface {
 public:
  Accelerometer() = delete;
  ~Accelerometer() = default;

  explicit Accelerometer(std::shared_ptr<i2c::I2CInterface> i2c_handler) : AccelerometerInterface(i2c_handler){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
};

}  // namespace imu

#endif