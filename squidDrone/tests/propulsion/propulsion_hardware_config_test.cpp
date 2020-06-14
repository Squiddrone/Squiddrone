#include "propulsion_hardware_config.hpp"

#include "gtest/gtest.h"
#include "propulsion_hardware_types.hpp"
#include "stm32g4xx.h"

namespace {

TEST(propulsion_hardware_config_test, is_constructible_and_exists) {
  TIM_HandleTypeDef timer;
  propulsion::PropulsionHardwareConfig unit_under_test{
      types::MotorType::LETODAR_2204, types::EscType::LITTLE_BEE_20_A, &timer, HAL_TIM_ACTIVE_CHANNEL_1};
  ASSERT_EQ(types::MotorType::LETODAR_2204, unit_under_test.motor_type);
  ASSERT_EQ(types::EscType::LITTLE_BEE_20_A, unit_under_test.esc_type);
  ASSERT_EQ(&timer, unit_under_test.timer);
  ASSERT_EQ(HAL_TIM_ACTIVE_CHANNEL_1, unit_under_test.channel);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}