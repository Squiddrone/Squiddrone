#ifndef SRC_TEMPERATURE_HPP_
#define SRC_TEMPERATURE_HPP_

#include "temperature_virtual_interface.hpp"

namespace imu {

class Temperature final : public TemperatureInterface {
 public:
  Temperature() = delete;
  ~Temperature() = default;

  explicit Temperature(std::shared_ptr<i2c::I2CInterface> i2c_handler) : TemperatureInterface(i2c_handler){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update_(void) noexcept -> types::DriverStatus override;
  auto Get_(void) noexcept -> std::int16_t override;

 private:
  std::int16_t sensor_value_ = -1;
};

}  // namespace imu

#endif