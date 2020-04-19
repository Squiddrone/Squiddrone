#ifndef SRC_MPU9250_HPP_
#define SRC_MPU9250_HPP_

#include "generic_imu.hpp"

namespace imu
{

  class Mpu9250 final : public GenericInertialMeasurementUnit
  {
  public:
    Mpu9250() = delete;
    ~Mpu9250() = default;
    explicit Mpu9250(i2c::I2CHandler i2c_handler): GenericInertialMeasurementUnit(i2c_handler), i2c_handler_(i2c_handler){}
    void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept override;
    types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept override;
    void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept override;
    types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept override;
    types::EuclideanVector<float> GetGyroscope(void) noexcept override;
    types::EuclideanVector<float> GetAccelerometer(void) noexcept override;
    types::EuclideanVector<float> GetMagnetometer(void) noexcept override;
    int GetTemperature(void) noexcept override;
  private:
    types::GyroscopeSensitivity gyroscope_sensitivity_ = types::GyroscopeSensitivity::FINEST;
    types::AccelerometerSensitivity accelerometer_sensitivity_ = types::AccelerometerSensitivity::FINEST;
    i2c::I2CHandler i2c_handler_;
  };

} // namespace imu

#endif