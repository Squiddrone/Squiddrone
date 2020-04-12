#include "gtest/gtest.h"
#include "imu_interface.hpp"

namespace{

  TEST(imu_interface, always_failed){
    EXPECT_EQ(1, 2);
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}