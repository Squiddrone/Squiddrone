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
  types::SPIStatus rv = unit_under_test_->Transfer(miso_buffer, too_large_buffer);
  EXPECT_EQ(rv, types::SPIStatus::SPI_BUFFER_SIZE_LIMIT_EXCEEDED);
}

TEST_F(SPITests, successful_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  types::SPIStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::SPIStatus::SPI_TRANSACTION_SUCCESSFUL);
}

TEST_F(SPITests, unsuccessful_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_TIMEOUT;
  types::SPIStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::SPIStatus::SPI_TRANSACTION_FAILED);
}

TEST_F(SPITests, spi_hal_error) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_ERROR;
  types::SPIStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::SPIStatus::SPI_HAL_ERROR);
}

}  // namespace