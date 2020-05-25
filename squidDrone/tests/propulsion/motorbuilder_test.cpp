#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "motor_builder.hpp"
#include "motor_mock.hpp"
#include "propulsion_hardware_config_mock.hpp"


namespace{
  TEST(motorbuilder_test, creates_correct_object){
    propulsion::PropulsionHardwareConfig config{};
    config.esc_type = types::EscType::LITTLE_BEE_20_A;
    config.motor_type = types::MotorType::LETODAR_2204;
    auto motor_object = propulsion::MotorBuilder::Create(config);
    ASSERT_EQ(motor_object->is_created_, true);
  }

  TEST(motorbuilder_test, creates_nullpointer){
    propulsion::PropulsionHardwareConfig config{};
    config.motor_type = types::MotorType::NONE;
    config.esc_type = types::EscType::LITTLE_BEE_20_A;
    auto motor_object = propulsion::MotorBuilder::Create(config);
    ASSERT_EQ(motor_object, nullptr);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}