#include "gtest/gtest.h"

namespace {
class MotorDriverTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
};

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}