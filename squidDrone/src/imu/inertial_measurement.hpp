#ifndef SRC_IM_HPP_
#define SRC_IM_HPP_

#include "imu_interface.hpp"
#include "mpu9250.hpp"

namespace imu
{

  class InertialMeasurement final : public InertialMeasurementInterface
  {
  public:
    InertialMeasurement() = delete;
    ~InertialMeasurement() = default;
    explicit InertialMeasurement(std::unique_ptr<i2c::I2CHandler> i2c_handler): InertialMeasurementInterface(std::move(i2c_handler)), mpu9250_(std::move(i2c_handler)){}
    void SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept override;
    types::GyroscopeSensitivity GetGyroscopeSensitivity(void) noexcept override;
    void SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept override;
    types::AccelerometerSensitivity GetAccelerometerSensitivity(void) noexcept override;
    types::EuclideanVector<float> GetGyroscope(void) noexcept override;
    types::EuclideanVector<float> GetAccelerometer(void) noexcept override;
    types::EuclideanVector<float> GetMagnetometer(void) noexcept override;
    int GetTemperature(void) noexcept override;
  protected:
    imu::Mpu9250 mpu9250_;
  };

} // namespace imu

#endif