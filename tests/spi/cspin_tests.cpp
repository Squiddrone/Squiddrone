#include "cspin.hpp"
#include "gtest/gtest.h"

namespace {

class CSPinTests : public ::testing::Test {
 protected:
  std::unique_ptr<spi::CSPin> unit_under_test_;
};
}  // namespace

TEST_F(CSPinTests, active_high_set_cs) {
  GPIO_TypeDef mock_gpio_typedef;
  mock_gpio_typedef.mock_test_value = GPIO_PIN_RESET;

  unit_under_test_ = std::make_unique<spi::CSPin>(&mock_gpio_typedef, 0, spi::CSActiveState::ACTIVE_HIGH);
  unit_under_test_->SetCSActive();
  EXPECT_EQ(mock_gpio_typedef.mock_test_value, (GPIO_PinState)GPIO_PinState::GPIO_PIN_SET);
}

TEST_F(CSPinTests, active_high_reset_cs) {
  GPIO_TypeDef mock_gpio_typedef;
  mock_gpio_typedef.mock_test_value = GPIO_PIN_SET;

  unit_under_test_ = std::make_unique<spi::CSPin>(&mock_gpio_typedef, 0, spi::CSActiveState::ACTIVE_HIGH);
  unit_under_test_->SetCSInactive();
  EXPECT_EQ(mock_gpio_typedef.mock_test_value, (GPIO_PinState)GPIO_PinState::GPIO_PIN_RESET);
}

TEST_F(CSPinTests, active_low_set_cs) {
  GPIO_TypeDef mock_gpio_typedef;
  mock_gpio_typedef.mock_test_value = GPIO_PIN_RESET;

  unit_under_test_ = std::make_unique<spi::CSPin>(&mock_gpio_typedef, 0, spi::CSActiveState::ACTIVE_LOW);
  unit_under_test_->SetCSActive();
  EXPECT_EQ(mock_gpio_typedef.mock_test_value, (GPIO_PinState)GPIO_PinState::GPIO_PIN_RESET);
}

TEST_F(CSPinTests, active_low_reset_cs) {
  GPIO_TypeDef mock_gpio_typedef;
  mock_gpio_typedef.mock_test_value = GPIO_PIN_SET;

  unit_under_test_ = std::make_unique<spi::CSPin>(&mock_gpio_typedef, 0, spi::CSActiveState::ACTIVE_LOW);
  unit_under_test_->SetCSInactive();
  EXPECT_EQ(mock_gpio_typedef.mock_test_value, (GPIO_PinState)GPIO_PinState::GPIO_PIN_SET);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}