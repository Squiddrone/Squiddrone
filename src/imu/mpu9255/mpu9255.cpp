#include "mpu9255.hpp"
#include "math.h"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  CreateSensorPointer();

  SetInitConfigMPU9255();

  if (InitAllSensors()) {
    SetToInitialized();

    UpdateAllSensors();
    GetFactoryOffsetValues();
    SetAccelBandwidth(accel::Bandwidth::acc_5Hz);
    SetGyroBandwidth(gyro::Bandwidth::gyro_5Hz);
    AdjustOffset();
    SetGyroBandwidth(gyro::Bandwidth::gyro_8800Hz);
    SetAccelBandwidth(accel::Bandwidth::acc_184Hz);

    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::CreateSensorPointer(void) noexcept -> void {
  if (gyroscope_ == nullptr) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == nullptr) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }
  if (magnetometer_ == nullptr) {
    magnetometer_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }
  if (temperature_ == nullptr) {
    temperature_ = std::make_unique<imu::Temperature>(i2c_handler_);
  }
}

auto Mpu9255::SetInitConfigMPU9255(void) noexcept -> void {
  auto int_pin_cfg_value = std::make_unique<utilities::Byte>(0);
  int_pin_cfg_value->SetBit(1);  // Set I2C Master of MPU9255 to Bypass mode
  int_pin_cfg_value->SetBit(5);  // Held Pin Level until interrupt status was cleared.
  SetMPU9255Register(INT_PIN_CFG, int_pin_cfg_value->Get());

  auto int_enable_value = std::make_unique<utilities::Byte>(0);
  int_enable_value->SetBit(0);  // Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin.
  SetMPU9255Register(INT_ENABLE, int_enable_value->Get());
}

auto Mpu9255::SetMPU9255Register(const std::uint8_t register_, const std::uint8_t register_value) noexcept -> void {
  i2c_handler_->Write(MPU9255_ADDRESS, {register_, register_value});
}

auto Mpu9255::GetMPU9255Register(const std::uint8_t register_, const std::uint16_t register_size) noexcept -> std::vector<std::uint8_t> {
  auto register_content = i2c_handler_->ReadContentFromRegister(MPU9255_ADDRESS, register_, register_size);
  return register_content.second;
}

auto Mpu9255::InitAllSensors(void) noexcept -> bool {
  return (gyroscope_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK &&
          accelerometer_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK &&
          magnetometer_->Init(AK8963_ADDRESS) == types::DriverStatus::OK &&
          temperature_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK);
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (UpdateAllSensors()) {
    SetToInitialized();
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::SetToInitialized(void) noexcept -> void {
  initialized_ = true;
}

auto Mpu9255::UpdateAllSensors(void) noexcept -> bool {
  return (gyroscope_->Update() == types::DriverStatus::OK &&
          accelerometer_->Update() == types::DriverStatus::OK &&
          magnetometer_->Update() == types::DriverStatus::OK &&
          temperature_->Update() == types::DriverStatus::OK);
}

auto Mpu9255::SetGyroscopeSensitivity(const types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return gyroscope_->SetSensitivity(gyroscope_sensitivity);
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  if (!IsInitialized())
    return types::ImuSensitivity::FINEST;

  return gyroscope_->GetSensitivity();
}

auto Mpu9255::SetAccelerometerSensitivity(const types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return accelerometer_->SetSensitivity(accelerometer_sensitivity);
}

auto Mpu9255::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
  if (!IsInitialized())
    return types::ImuSensitivity::FINEST;

  return accelerometer_->GetSensitivity();
}

auto Mpu9255::GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return gyroscope_->Get();
}

auto Mpu9255::GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return accelerometer_->Get();
}

auto Mpu9255::GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return magnetometer_->Get();
}

auto Mpu9255::ReturnVectorDefault(void) noexcept -> types::EuclideanVector<std::int16_t> {
  return types::EuclideanVector<std::int16_t>{-1, -1, -1};
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  if (!IsInitialized())
    return -1;

  return temperature_->Get();
}

auto Mpu9255::GetFactoryOffsetValues(void) noexcept -> void {
  auto gx_offset_h = GetMPU9255Register(GYRO_X_OFFSET_H, 1).at(0);
  auto gx_offset_l = GetMPU9255Register(GYRO_X_OFFSET_L, 1).at(0);
  auto gy_offset_h = GetMPU9255Register(GYRO_Y_OFFSET_H, 1).at(0);
  auto gy_offset_l = GetMPU9255Register(GYRO_Y_OFFSET_L, 1).at(0);
  auto gz_offset_h = GetMPU9255Register(GYRO_Z_OFFSET_H, 1).at(0);
  auto gz_offset_l = GetMPU9255Register(GYRO_Z_OFFSET_L, 1).at(0);

  gyro_offset.x = static_cast<int16_t>((gx_offset_h << 8) | gx_offset_l);
  gyro_offset.y = static_cast<int16_t>((gy_offset_h << 8) | gy_offset_l);
  gyro_offset.z = static_cast<int16_t>((gz_offset_h << 8) | gz_offset_l);

  auto ax_offset_h = GetMPU9255Register(ACCEL_X_OFFSET_H, 1).at(0);
  auto ax_offset_l = GetMPU9255Register(ACCEL_X_OFFSET_L, 1).at(0);
  auto ay_offset_h = GetMPU9255Register(ACCEL_Y_OFFSET_H, 1).at(0);
  auto ay_offset_l = GetMPU9255Register(ACCEL_Y_OFFSET_L, 1).at(0);
  auto az_offset_h = GetMPU9255Register(ACCEL_Z_OFFSET_H, 1).at(0);
  auto az_offset_l = GetMPU9255Register(ACCEL_Z_OFFSET_L, 1).at(0);

  accel_offset.x = static_cast<int16_t>((ax_offset_h << 8) | ax_offset_l);
  accel_offset.y = static_cast<int16_t>((ay_offset_h << 8) | ay_offset_l);
  accel_offset.z = static_cast<int16_t>((az_offset_h << 8) | az_offset_l);
}

auto Mpu9255::SetGyroOffset(types::EuclideanVector<int16_t> offset, Axis axis) noexcept -> void {
  std::int16_t offset_x, offset_y, offset_z;
  switch (axis) {
    case Axis::X_AXIS:
      offset_x = gyro_offset.x + offset.x;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_X_OFFSET_L, (offset_x & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_X_OFFSET_H, (offset_x >> 8));    // write high byte
      break;
    case Axis::Y_AXIS:
      offset_y = gyro_offset.y + offset.y;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_Y_OFFSET_L, (offset_y & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_Y_OFFSET_H, (offset_y >> 8));    // write high byte
      break;
    case Axis::Z_AXIS:
      offset_z = gyro_offset.z + offset.z;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_Z_OFFSET_L, (offset_z & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_Z_OFFSET_H, (offset_z >> 8));    // write high byte
      break;
    case Axis::ALL:
      offset_x = gyro_offset.x + offset.x;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_X_OFFSET_L, (offset_x & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_X_OFFSET_H, (offset_x >> 8));    // write high byte
      offset_y = gyro_offset.y + offset.y;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_Y_OFFSET_L, (offset_y & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_Y_OFFSET_H, (offset_y >> 8));    // write high byte
      offset_z = gyro_offset.z + offset.z;                     // add offset to the factory offset
      SetMPU9255Register(GYRO_Z_OFFSET_L, (offset_z & 0xFF));  // write low byte
      SetMPU9255Register(GYRO_Z_OFFSET_H, (offset_z >> 8));    // write high byte
      break;
  }
}

auto Mpu9255::SetAccelOffset(types::EuclideanVector<int16_t> offset, Axis axis) noexcept -> void {
  std::int16_t offset_x, offset_y, offset_z;
  switch (axis) {
    case Axis::X_AXIS:
      offset_x = accel_offset.x + offset.x;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_X_OFFSET_L, ((offset_x & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_X_OFFSET_H, (offset_x >> 7));           // write high byte
      break;
    case Axis::Y_AXIS:
      offset_y = accel_offset.y + offset.y;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_Y_OFFSET_L, ((offset_y & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_Y_OFFSET_H, (offset_y >> 7));           // write high byte
      break;
    case Axis::Z_AXIS:
      offset_z = accel_offset.z + offset.z;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_Z_OFFSET_L, ((offset_z & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_Z_OFFSET_H, (offset_z >> 7));           // write high byte
      break;
    case Axis::ALL:
      offset_x = accel_offset.x + offset.x;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_X_OFFSET_L, ((offset_x & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_X_OFFSET_H, (offset_x >> 7));           // write high byte
      offset_y = accel_offset.y + offset.y;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_Y_OFFSET_L, ((offset_y & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_Y_OFFSET_H, (offset_y >> 7));           // write high byte
      offset_z = accel_offset.z + offset.z;                            // add offset to the factory offset
      SetMPU9255Register(ACCEL_Z_OFFSET_L, ((offset_z & 0xFF) << 1));  // write low byte
      SetMPU9255Register(ACCEL_Z_OFFSET_H, (offset_z >> 7));           // write high byte
      break;
  }
}

auto Mpu9255::SetAccelBandwidth(accel::Bandwidth bandwidth) noexcept -> void {
  std::unique_ptr<utilities::Byte> accel_config_2_reg = nullptr;
  switch (bandwidth) {
    case accel::Bandwidth::acc_1113Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetBit(3);
      // write_OR(MPU_address, ACCEL_CONFIG_2, (1 << 3));  // set accel_fchoice_b to 1
      break;

    case accel::Bandwidth::acc_460Hz:
      // set accel_fchoice_b to 0 and  A_DLPF_CFG to 0(000)
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0U);
      break;

    case accel::Bandwidth::acc_184Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x1U);
      break;

    case accel::Bandwidth::acc_92Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x2U);
      break;

    case accel::Bandwidth::acc_41Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x3U);
      break;

    case accel::Bandwidth::acc_20Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x4U);
      break;

    case accel::Bandwidth::acc_10Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x5U);
      break;

    case accel::Bandwidth::acc_5Hz:
      accel_config_2_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(ACCEL_CONFIG_2, 1).at(0));
      accel_config_2_reg->SetLowNibble(0x6U);
      break;
  }
  if (accel_config_2_reg != nullptr) {
    // SetMPU9255Register(ACCEL_CONFIG_2, accel_config_2_reg->Get());
  }
}

auto Mpu9255::SetGyroBandwidth(gyro::Bandwidth bandwidth) noexcept -> void {
  std::unique_ptr<utilities::Byte> gyro_config_reg = nullptr;
  std::unique_ptr<utilities::Byte> mpu_config_reg = nullptr;

  switch (bandwidth) {
    case gyro::Bandwidth::gyro_8800Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->SetBit(0);
      break;
    case gyro::Bandwidth::gyro_3600Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->SetBit(1);
      break;

    case gyro::Bandwidth::gyro_250Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->ClearBit(0);
      mpu_config_reg->ClearBit(1);
      mpu_config_reg->ClearBit(2);
      break;
    case gyro::Bandwidth::gyro_184Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->SetBit(0);
      mpu_config_reg->ClearBit(1);
      mpu_config_reg->ClearBit(2);
      break;
    case gyro::Bandwidth::gyro_92Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->ClearBit(0);
      mpu_config_reg->SetBit(1);
      mpu_config_reg->ClearBit(2);
      break;
    case gyro::Bandwidth::gyro_41Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->SetBit(0);
      mpu_config_reg->SetBit(1);
      mpu_config_reg->ClearBit(2);
      break;
    case gyro::Bandwidth::gyro_20Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->ClearBit(0);
      mpu_config_reg->ClearBit(1);
      mpu_config_reg->SetBit(2);
      break;
    case gyro::Bandwidth::gyro_10Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->SetBit(0);
      mpu_config_reg->ClearBit(1);
      mpu_config_reg->SetBit(2);
      break;
    case gyro::Bandwidth::gyro_5Hz:
      gyro_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(GYRO_CONFIG, 1).at(0));
      gyro_config_reg->ClearBit(0);
      gyro_config_reg->ClearBit(1);
      mpu_config_reg = std::make_unique<utilities::Byte>(GetMPU9255Register(MPU_CONFIG, 1).at(0));
      mpu_config_reg->ClearBit(0);
      mpu_config_reg->SetBit(1);
      mpu_config_reg->SetBit(2);
      break;
  }

  if (gyro_config_reg != nullptr) {
    SetMPU9255Register(GYRO_CONFIG, gyro_config_reg->Get());
  }
  if (mpu_config_reg != nullptr) {
    SetMPU9255Register(MPU_CONFIG, mpu_config_reg->Get());
  }
}

auto Mpu9255::AdjustOffset(void) noexcept -> void {
  const auto max_error_gyro = 1;
  const auto max_error_accel = 1;

  enum lock : int8_t {
    locked = -1,
    unlocked = 1
  };

  struct AxisLock {
    explicit AxisLock(lock x, lock y, lock z) : x(unlocked), y(unlocked), z(unlocked){};
    lock x;
    lock y;
    lock z;
  };

  types::EuclideanVector<int16_t>
      gyro_offset(0, 0, 0);
  types::EuclideanVector<int16_t> accel_offset(0, 0, 0);
  AxisLock lock_gyro_offset(unlocked, unlocked, unlocked);
  AxisLock lock_accel_offset(unlocked, unlocked, unlocked);

  Update();  // First reading is discarded.

  utilities::Sleep(10);

  while (1) {
    Update();
    auto gyro_output = GetGyroscope();
    auto accel_output = GetAccelerometer();

    if (lock_gyro_offset.x == unlocked && gyro_output.x < 0) {
      ++gyro_offset.x;
    }
    if (lock_gyro_offset.x == unlocked && gyro_output.x > 0) {
      --gyro_offset.x;
    }
    if (lock_gyro_offset.y == unlocked && gyro_output.y < 0) {
      ++gyro_offset.y;
    }
    if (lock_gyro_offset.y == unlocked && gyro_output.y > 0) {
      --gyro_offset.y;
    }
    if (lock_gyro_offset.z == unlocked && gyro_output.z < 0) {
      ++gyro_offset.z;
    }
    if (lock_gyro_offset.z == unlocked && gyro_output.z > 0) {
      --gyro_offset.z;
    }
    if (lock_accel_offset.x == unlocked && accel_output.x < 0) {
      ++accel_offset.x;
    }
    if (lock_accel_offset.x == unlocked && accel_output.x > 0) {
      --accel_offset.x;
    }
    if (lock_accel_offset.y == unlocked && accel_output.y < 0) {
      ++accel_offset.y;
    }
    if (lock_accel_offset.y == unlocked && accel_output.y > 0) {
      --accel_offset.y;
    }
    if (lock_accel_offset.z == unlocked && accel_output.z < 0) {
      ++accel_offset.z;
    }
    if (lock_accel_offset.z == unlocked && accel_output.z > 0) {
      --accel_offset.z;
    }

    if ((abs(gyro_output.x) - max_error_gyro) <= 0) {
      lock_gyro_offset.x = locked;
    }
    if ((abs(gyro_output.y) - max_error_gyro) <= 0) {
      lock_gyro_offset.y = locked;
    }
    if ((abs(gyro_output.z) - max_error_gyro) <= 0) {
      lock_gyro_offset.z = locked;
    }
    if ((abs(accel_output.x) - max_error_accel) <= 0) {
      lock_accel_offset.x = locked;
    }
    if ((abs(accel_output.y) - max_error_accel) <= 0) {
      lock_accel_offset.y = locked;
    }
    if ((abs(accel_output.z) - max_error_accel) <= 0) {
      lock_accel_offset.z = locked;
    }

    if (lock_gyro_offset.x == locked &&
        lock_gyro_offset.y == locked &&
        lock_gyro_offset.z == locked &&
        lock_accel_offset.x == locked &&
        lock_accel_offset.y == locked &&
        lock_accel_offset.z == locked) {
      break;
    }
    SetGyroOffset(gyro_offset, Axis::ALL);
    SetAccelOffset(accel_offset, Axis::ALL);
  }
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) noexcept -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) noexcept -> void {
  accelerometer_ = std::move(accelerometer);
}

auto Mpu9255::UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) noexcept -> void {
  magnetometer_ = std::move(magnetometer);
}

auto Mpu9255::UnitTestSetTemperature(std::unique_ptr<imu::TemperatureInterface> temperature) noexcept -> void {
  temperature_ = std::move(temperature);
}

}  // namespace imu
