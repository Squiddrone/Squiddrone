#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "motor_builder.hpp"
#include "motor_mock.hpp"
#include "propulsion_hardware_config_mock.hpp"
#include "stm32g4xx.h"

namespace {

class MotorBuilderTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    timer.test_member = 0;
    config.motor_type = types::MotorType::LETODAR_2204;
    config.esc_type = types::EscType::LITTLE_BEE_20_A;
    config.timer = &timer;
    config.channel = HAL_TIM_ACTIVE_CHANNEL_1;
  }

  propulsion::PropulsionHardwareConfig config;
  TIM_HandleTypeDef timer;
};

TEST_F(MotorBuilderTest, creates_correct_object) {
  auto motor_object = propulsion::MotorBuilder::Create(config);
  ASSERT_EQ(motor_object->is_created_, true);
}

TEST_F(MotorBuilderTest, creates_nullpointer) {
  config.motor_type = types::MotorType::NONE;
  auto motor_object = propulsion::MotorBuilder::Create(config);
  ASSERT_EQ(motor_object, nullptr);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}