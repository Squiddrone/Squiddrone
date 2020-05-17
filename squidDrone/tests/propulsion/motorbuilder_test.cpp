#include "gtest/gtest.h"
#include "motor_builder.hpp"
#include "propulsion_hardware_config_mock.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}