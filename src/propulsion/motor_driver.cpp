#include <cstdlib>

#ifndef UNIT_TEST
#include "motor_builder.hpp"
#else
#include "motor_builder_mock.hpp"
#endif
#include "motor_driver.hpp"
#include "timer_config.h"

namespace propulsion {

MotorDriver::MotorDriver() : motors_{} {
  auto motor_type = types::MotorType::LETODAR_2204;
  auto esc_type = types::EscType::LITTLE_BEE_20_A;
  PropulsionHardwareConfig config_left_front{motor_type, esc_type, &htim2, TIM_CHANNEL_1};
  PropulsionHardwareConfig config_right_front{motor_type, esc_type, &htim17, TIM_CHANNEL_1};
  PropulsionHardwareConfig config_left_rear{motor_type, esc_type, &htim16, TIM_CHANNEL_1};
  PropulsionHardwareConfig config_right_rear{motor_type, esc_type, &htim2, TIM_CHANNEL_2};
  InitializeMotor(MotorPosition::LEFT_FRONT, config_left_front);
  InitializeMotor(MotorPosition::RIGHT_FRONT, config_right_front);
  InitializeMotor(MotorPosition::LEFT_REAR, config_left_rear);
  InitializeMotor(MotorPosition::RIGHT_REAR, config_right_rear);
}

auto MotorDriver::InitializeMotor(MotorPosition position, PropulsionHardwareConfig &config) noexcept -> void {
  auto motor = MotorBuilder::Create(config);
  if (motor == nullptr) {
    std::abort();
  } else {
    motors_.at(static_cast<int>(position)) = std::move(motor);
  }
}

auto MotorDriver::SetMotorSpeed(const MotorPosition which_motor, const float speed) const noexcept -> const types::DriverStatus {
  const float min_speed = 0;
  const float max_speed = 100;
  if (speed < min_speed || speed > max_speed) {
    return types::DriverStatus::INPUT_ERROR;
  } else {
    auto status = motors_.at(static_cast<int>(which_motor))->SetSpeedInPercent(speed);
    if (status != types::DriverStatus::OK) {
      return types::DriverStatus::HAL_ERROR;
    } else {
      return types::DriverStatus::OK;
    }
  }
}

auto MotorDriver::GetMotorSpeed(const MotorPosition which_motor) const noexcept -> std::pair<float, types::DriverStatus> {
  auto speed = motors_.at(static_cast<int>(which_motor))->GetCurrentSpeedInPercent();
  return std::pair<float, types::DriverStatus>{speed, types::DriverStatus::OK};
}

}  // namespace propulsion
