#ifndef SRC_MAGNETOMETER_HPP_
#define SRC_MAGNETOMETER_HPP_

#include "magnetometer_virtual_interface.hpp"
#include "sleep.hpp"

namespace imu {

class Magnetometer final : public MagnetometerInterface {
 public:
  Magnetometer() = delete;
  ~Magnetometer() = default;

  explicit Magnetometer(std::shared_ptr<i2c::I2CInterface> i2c_handler) : MagnetometerInterface(i2c_handler){};
  auto Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;

 private:
  types::EuclideanVector<float> calibration_values_{-1, -1, -1};
  float MAX_MAGNETIC_FLUX_IN_MICRO_TESLA = 4912.0f;
  float MAX_MAGNETIC_MEASUREMENT_IN_DIGIT_16BIT = 32760.0f;

  auto SetInitData(void) -> void;
  auto IsMagnetometerMeasurementReady(void) noexcept -> bool;
  auto HasMagnetometerOverflow(const std::uint8_t st2_register_value) noexcept -> bool;
  auto GetFactorADC2Magnetometer(void) noexcept -> float;
  auto GetCalibrationValues(void) noexcept -> void;
};

}  // namespace imu

#endif