#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spi.hpp"

namespace {

class SPITests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<spi::SPI>(cs_pin);
  }

  spi::CSPin cs_pin = {.peripheral = nullptr, .gpio_pin = 0};
  std::unique_ptr<spi::SPI> unit_under_test_;
  std::vector<uint8_t> miso_buffer;
  std::vector<uint8_t> mosi_buffer;
};

TEST_F(SPITests, exceeding_buffer_size_limit) {
  std::vector<uint8_t> too_large_buffer(65);
  types::DriverStatus rv = unit_under_test_->Transfer(mosi_buffer, too_large_buffer);
  EXPECT_EQ(rv, types::DriverStatus::INPUT_ERROR);
}

TEST_F(SPITests, buffer_size_limit_at_maximum) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<uint8_t> miso_buffer(64);
  types::DriverStatus rv = unit_under_test_->Transfer(mosi_buffer, miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, buffer_size_limit_zero) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<uint8_t> zero_size_buffer(0);
  types::DriverStatus rv = unit_under_test_->Transfer(zero_size_buffer, miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, miso_buffer_too_small) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<uint8_t> mosi_buffer(5);
  std::vector<uint8_t> small_miso_buffer(0);
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, small_miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, successful_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, timeout_during_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_TIMEOUT;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::TIMEOUT);
}

TEST_F(SPITests, spi_hal_error) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_ERROR;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

TEST_F(SPITests, spi_hal_busy) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_BUSY;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

}  // namespace