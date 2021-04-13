#ifndef SRC_IMU_MEASUREMENT_SENSOR_VECTOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_VECTOR_HPP_

#include "sensor_vector_interface.hpp"

namespace imu {

class SensorVector : public SensorVectorInterface {
 public:
  virtual ~SensorVector() = default;

  explicit SensorVector(std::shared_ptr<i2c::I2CInterface> i2c_handler) : SensorVectorInterface(i2c_handler){};
  auto Update(void) noexcept -> types::DriverStatus override;
  auto Get(void) noexcept -> types::EuclideanVector<int16_t> override;

 protected:
  auto SetSensorValues(const std::vector<std::int16_t> &sensor_values) noexcept -> void;

  static constexpr std::uint8_t POSITION_X = 0;
  static constexpr std::uint8_t POSITION_Y = 1;
  static constexpr std::uint8_t POSITION_Z = 2;

  types::EuclideanVector<std::int16_t> sensor_values_{-1, -1, -1};
};

}  // namespace imu

#endif