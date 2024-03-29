#include "motor_driver.hpp"
#include <cstdlib>
#include "stm32g4xx_hal.h"
#include "timer_config.h"
#ifndef UNIT_TEST
#include "sleep.hpp"
#else
#include "sleep_mock.hpp"
#endif

namespace propulsion {

MotorDriver::MotorDriver(std::unique_ptr<AbstractMotorBuilder> builder) : AbstractMotorDriver(), motor_builder_(std::move(builder)), motors_{} {
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
  auto motor = motor_builder_->Create(config);
  motors_.at(static_cast<int>(position)) = std::move(motor);
}

auto MotorDriver::SetMotorSpeed(const MotorPosition which_motor, const float speed) const noexcept -> const types::DriverStatus {
  constexpr float min_speed = 0.0;
  constexpr float max_speed = 100.0;
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

auto MotorDriver::GetMotorSpeed(const MotorPosition which_motor) const noexcept -> std::pair<types::DriverStatus, float> {
  constexpr float minimum_speed_in_percent = 0.0;
  constexpr float maximum_speed_in_percent = 100.0;
  auto speed = motors_.at(static_cast<int>(which_motor))->GetCurrentSpeedInPercent();
  if (speed < minimum_speed_in_percent || speed > maximum_speed_in_percent) {
    return std::pair<types::DriverStatus, float>(types::DriverStatus::HAL_ERROR, -1);
  } else {
    return std::pair<types::DriverStatus, float>{types::DriverStatus::OK, speed};
  }
}

auto MotorDriver::ArmEscs() const noexcept -> const types::DriverStatus {
  constexpr float max_speed = 100.0;
  constexpr float min_speed = 0.0;

  auto status = SetSpeedForAllMotors(min_speed);
  if (status != types::DriverStatus::OK) {
    return status;
  }
  utilities::Sleep(DELAY_TIME_MS_);
  status = SetSpeedForAllMotors(max_speed);
  if (status != types::DriverStatus::OK) {
    return status;
  }
  utilities::Sleep(DELAY_TIME_MS_);
  status = SetSpeedForAllMotors(min_speed);
  if (status != types::DriverStatus::OK) {
    return status;
  }
  return types::DriverStatus::OK;
}

auto MotorDriver::SetSpeedForAllMotors(const float speed) const noexcept -> const types::DriverStatus {
  for (auto &&motor : motors_) {
    auto status = motor->SetSpeedInPercent(speed);
    if (status != types::DriverStatus::OK) {
      return status;
    }
  }
  return types::DriverStatus::OK;
}

}  // namespace propulsion
