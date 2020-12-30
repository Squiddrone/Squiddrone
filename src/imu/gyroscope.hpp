#ifndef SRC_GYROSCOPE_HPP_
#define SRC_GYROSCOPE_HPP_

#include "gyroscope_virtual_interface.hpp"
#include "imu_sensitivity.hpp"
#include "imu_sensor_with_sensitivity.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class Gyroscope final : public GyroscopeInterface {
 public:
  Gyroscope() = delete;
  ~Gyroscope() = default;

  explicit Gyroscope(std::unique_ptr<i2c::I2CInterface> i2c_handler) : GyroscopeInterface(std::move(i2c_handler)){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
};

}  // namespace imu

#endif