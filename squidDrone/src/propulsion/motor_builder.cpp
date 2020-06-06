#include "motor_builder.hpp"

#include <set>

#include "stm32g4xx_hal_tim.h"

#ifndef UNIT_TEST
#include "letodar_2204.hpp"
#include "little_bee_20_a.hpp"
#else
#include "letodar_2204_mock.hpp"
#include "little_bee_20_a_mock.hpp"
#endif
namespace propulsion {

auto MotorBuilder::Create(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> std::unique_ptr<Motor> {
  if (MotorConfigIsValid(motor_config)) {
    auto correct_esc = GetCorrectEsc(motor_config);
    std::unique_ptr<Motor> correct_motor;
    switch (motor_config.motor_type) {
      case types::MotorType::LETODAR_2204:
        correct_motor = std::make_unique<LeTodar2204>(std::move(correct_esc));
        break;
    }
    return correct_motor;
  } else {
    return nullptr;
  }
}

auto MotorBuilder::MotorConfigIsValid(propulsion::PropulsionHardwareConfig& motor_config) noexcept -> const bool {
  const std::set<std::uint32_t> possible_channels{TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4, TIM_CHANNEL_5, TIM_CHANNEL_6};
  const bool channel_is_in_possible_channels = possible_channels.find(motor_config.channel) != possible_channels.end();
  return (channel_is_in_possible_channels && motor_config.timer != nullptr);
}

auto MotorBuilder::GetCorrectEsc(propulsion::PropulsionHardwareConfig& config) noexcept -> std::unique_ptr<Esc> {
  std::unique_ptr<Esc> esc;
  switch (config.esc_type) {
    case types::EscType::LITTLE_BEE_20_A:
      esc = std::make_unique<LittleBee20A>(config.timer, config.channel);
      break;
  }
  return esc;
}

}  // namespace propulsion
