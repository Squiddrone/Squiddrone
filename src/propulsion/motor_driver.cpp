#include "motor_driver.hpp"
#include "motor_builder.hpp"
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

auto MotorDriver::InitializeMotor(MotorPosition position, PropulsionHardwareConfig &config) noexcept -> const types::DriverStatus {
  auto motor = MotorBuilder::Create(config);
  if (motor == nullptr) {
    return types::DriverStatus::INPUT_ERROR;
  } else {
    motors_.at(static_cast<int>(position)) = std::move(motor);
    return types::DriverStatus::OK;
  }
}

}  // namespace propulsion
