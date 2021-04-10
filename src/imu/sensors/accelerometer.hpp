#ifndef SRC_ACCELEROMETER_HPP_
#define SRC_ACCELEROMETER_HPP_

#include "accelerometer_interface.hpp"

namespace imu {

class Accelerometer final : public AccelerometerInterface {
 public:
  Accelerometer() = delete;
  ~Accelerometer() = default;

  explicit Accelerometer(std::shared_ptr<i2c::I2CInterface> i2c_handler) : AccelerometerInterface(i2c_handler){};
  auto Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;

 private:
  auto GetFactorADC2Accelerometer(void) noexcept -> float;
};

}  // namespace imu

#endif