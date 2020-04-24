#ifndef SRC_IM_HPP_
#define SRC_IM_HPP_

#include "imu_interface.hpp"

namespace imu {

  class InertialMeasurement final : public InertialMeasurementInterface {
    public:
      InertialMeasurement() = delete;
      ~InertialMeasurement() = default;
      explicit InertialMeasurement(std::unique_ptr<i2c::I2CHandler> i2c_handler): InertialMeasurementInterface(std::move(i2c_handler)){}
      void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept override;
      auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity override;
      void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept override;
      auto GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity override;
      auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> override;
      auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> override;
      auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> override;
      auto GetTemperature(void) noexcept -> int override;
  };

} // namespace imu

#endif