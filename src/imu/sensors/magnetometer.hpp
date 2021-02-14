#ifndef SRC_MAGNETOMETER_HPP_
#define SRC_MAGNETOMETER_HPP_

#include "magnetometer_virtual_interface.hpp"

namespace imu {

class Magnetometer final : public MagnetometerInterface {
 public:
  Magnetometer() = delete;
  ~Magnetometer() = default;

  explicit Magnetometer(std::shared_ptr<i2c::I2CInterface> i2c_handler) : MagnetometerInterface(i2c_handler){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;

 private:
  types::EuclideanVector<float> calibration_values_{-1, -1, -1};

  auto GetFactorADC2Magnetometer(void) noexcept -> float;
  auto GetCalibrationValues(void) noexcept -> void;
};

}  // namespace imu

#endif