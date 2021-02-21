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
  auto Update(void) noexcept -> types::DriverStatus override;

 private:
  auto CalculateTempInDegreeFromADC(std::int16_t adc_value) noexcept -> std::int16_t;
};

}  // namespace imu

#endif