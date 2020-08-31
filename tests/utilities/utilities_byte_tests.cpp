#include "gtest/gtest.h"
#include "utilities/byte.hpp"

namespace {

class UtilityByteTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  std::unique_ptr<utilities::Byte> unit_under_test_;
};

TEST_F(UtilityByteTests, byte_initialize_empty) {
  unit_under_test_ = std::make_unique<utilities::Byte>();

  EXPECT_EQ(0, unit_under_test_->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_5) {
  unit_under_test_ = std::make_unique<utilities::Byte>(5);

  EXPECT_EQ(5, unit_under_test_->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_0) {
  unit_under_test_ = std::make_unique<utilities::Byte>(0);

  EXPECT_EQ(0, unit_under_test_->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_255) {
  unit_under_test_ = std::make_unique<utilities::Byte>(255);

  EXPECT_EQ(255, unit_under_test_->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_minus_1) {
  unit_under_test_ = std::make_unique<utilities::Byte>(-1);

  EXPECT_EQ(0, unit_under_test_->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_256) {
  unit_under_test_ = std::make_unique<utilities::Byte>(256);

  EXPECT_EQ(0, unit_under_test_->Get());
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}