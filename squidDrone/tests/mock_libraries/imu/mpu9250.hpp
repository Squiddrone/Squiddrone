#ifndef MOCK_Mpu9250_HPP_
#define MOCK_Mpu9250_HPP_

#include "accelerometer_sensitivity.hpp"
#include "basic_types.hpp"
#include "gyroscope_sensitivity.hpp"
#include "i2c_handler.hpp"
#include "generic_imu.hpp"

namespace imu {

/// Mocklibrary for MPU9250
class Mpu9250 final : public GenericInertialMeasurementUnit{
  public:
    Mpu9250() = delete;
    ~Mpu9250() = default;
    explicit Mpu9250(i2c::I2CHandler i2c_handler): GenericInertialMeasurementUnit(i2c_handler), i2c_handler_(i2c_handler){}
    void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept;
    types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept;
    void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept;
    types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept;
    types::EuclideanVector<float> GetGyroscope(void) noexcept;
    types::EuclideanVector<float> GetAccelerometer(void) noexcept;
    types::EuclideanVector<float> GetMagnetometer(void) noexcept;
    int GetTemperature(void) noexcept;
  private:
    types::GyroscopeSensitivity gyroscope_sensitivity_ = types::GyroscopeSensitivity::FINEST;
    types::AccelerometerSensitivity accelerometer_sensitivity_ = types::AccelerometerSensitivity::FINEST;
    i2c::I2CHandler i2c_handler_;
};

}  // namespace imu

#endif