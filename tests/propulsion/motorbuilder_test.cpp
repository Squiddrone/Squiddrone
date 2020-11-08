#include <memory>
#include <type_traits>
#include <utility>

#include "gtest/gtest.h"
#include "letodar_2204_mock.hpp"
#include "motor_builder.hpp"
#include "propulsion_hardware_config_mock.hpp"
#include "stm32g4xx_hal_tim.h"

namespace {

class MotorBuilderTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    timer.test_member = 42;
    config.motor_type = types::MotorType::LETODAR_2204;
    config.esc_type = types::EscType::LITTLE_BEE_20_A;
    config.timer = &timer;
    config.channel = TIM_CHANNEL_2;
  }

  propulsion::PropulsionHardwareConfig config;
  TIM_HandleTypeDef timer;
  propulsion::MotorBuilder unit_under_test = propulsion::MotorBuilder();
};

//The dynamic upcast is used as a way of having the python function instanceof
TEST_F(MotorBuilderTest, creates_correct_object) {
  auto motor_object = unit_under_test.Create(config);
  auto upcast_object_pointer = dynamic_cast<propulsion::Motor *>(motor_object.get());
  ASSERT_TRUE(upcast_object_pointer != nullptr);
}

TEST_F(MotorBuilderTest, channel_is_not_in_allowed_channels) {
  config.channel = 666;
  auto motor_object = unit_under_test.Create(config);
  ASSERT_EQ(motor_object, nullptr);
}

TEST_F(MotorBuilderTest, timer_is_nullpointer) {
  config.timer = nullptr;
  auto motor_object = unit_under_test.Create(config);
  ASSERT_EQ(motor_object, nullptr);
}

TEST_F(MotorBuilderTest, esc_is_not_known) {
  config.esc_type = types::EscType::NONE;
  auto motor_object = unit_under_test.Create(config);
  ASSERT_EQ(motor_object, nullptr);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}