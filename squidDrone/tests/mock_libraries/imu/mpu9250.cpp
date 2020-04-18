#include "mpu9250.hpp"

namespace imu {

    void Mpu9250::SetGyroscopeSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept {

    }

    types::GyroscopeSensitivity Mpu9250::GetGyroscopeSensitivity(void) noexcept {
      return gyroscope_sensitivity;
    }

    void Mpu9250::SetAccelerometerSensitivity(types::AccelerometerSensitivity accelerometer_sensitivity) noexcept {

    }

    types::AccelerometerSensitivity Mpu9250::GetAccelerometerSensitivity(void) noexcept {
      return accelerometer_sensitivity;
    }

    types::EuclideanVector<float> Mpu9250::GetGyroscope(void) noexcept {
      types::EuclideanVector<float> value{1.5, 2.5, 3.5};
      return value;
    }

    types::EuclideanVector<float> Mpu9250::GetAccelerometer(void) noexcept {
      types::EuclideanVector<float> value{4.5, 5.5, 6.5};
      return value;
    }

    types::EuclideanVector<float> Mpu9250::GetMagnetometer(void) noexcept {
      types::EuclideanVector<float> value{7.5, 8.5, 9.5};
      return value;
    }

    int Mpu9250::GetTemperature(void) noexcept { 
      return 17; 
    }

}