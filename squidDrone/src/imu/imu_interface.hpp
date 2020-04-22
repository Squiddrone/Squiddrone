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
      virtual types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept = 0;
      virtual void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept = 0;
      virtual types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetGyroscope(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetAccelerometer(void) noexcept = 0;
      virtual types::EuclideanVector<float> GetMagnetometer(void) noexcept = 0;
      virtual int GetTemperature(void) noexcept = 0;
    protected:
      std::unique_ptr<imu::GenericInertialMeasurementUnit> mpu9250_;
  };

} // namespace imu

#endif