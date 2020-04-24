#ifndef SRC_IMU_INTERFACE_HPP_
#define SRC_IMU_INTERFACE_HPP_

#include "i2c_handler.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "accelerometer_sensitivity.hpp"
#include "mpu9250.hpp"

namespace imu {

  class InertialMeasurementInterface {
    public:
      InertialMeasurementInterface() = delete;
      virtual ~InertialMeasurementInterface() = default;
      explicit InertialMeasurementInterface(std::unique_ptr<i2c::I2CHandler> i2c_handler): mpu9250_(std::make_unique<imu::Mpu9250>(std::move(i2c_handler))){};
      virtual void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept = 0;
      virtual auto GetGyroscopeSensitivity(void) noexcept -> types::GyroscopeSensitivity = 0;
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept = 0;
      virtual auto GetAccelerometerSensitivity(void) noexcept -> types::AccelerometerSensitivity = 0;
      virtual auto GetGyroscope(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetAccelerometer(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetMagnetometer(void) noexcept -> types::EuclideanVector<float> = 0;
      virtual auto GetTemperature(void) noexcept -> int = 0;
    protected:
      std::unique_ptr<imu::GenericInertialMeasurementUnit> mpu9250_;
  };

} // namespace imu

#endif