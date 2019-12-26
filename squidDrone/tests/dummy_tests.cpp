
#include "gtest/gtest.h"

namespace {
  TEST(dummy, trivial_pass) {
    EXPECT_EQ(true, true);
  }

  TEST(dummy, trivial_fail) {
    EXPECT_EQ(true, false);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}