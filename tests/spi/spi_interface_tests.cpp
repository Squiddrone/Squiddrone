#include "gtest/gtest.h"
#include "spi_interface.hpp"

namespace {
class ConcreteSPIInterface final : public spi::SPIInterface {
 public:
  explicit ConcreteSPIInterface() : spi::SPIInterface(){};
  auto Write(std::vector<std::uint8_t> &TxData) noexcept -> types::DriverStatus override {
    return types::DriverStatus::OK;
  }
  auto Transfer(std::vector<std::uint8_t> &TxData, std::vector<std::uint8_t> &RxData) noexcept -> types::DriverStatus override {
    return types::DriverStatus::OK;
  };
};

class SpiInterfaceTests : public ::testing::Test {
 protected:
  std::unique_ptr<ConcreteSPIInterface> unit_under_test_;
};

TEST_F(SpiInterfaceTests, transfer) {
  auto Rx = std::vector<std::uint8_t>();
  auto Tx = std::vector<std::uint8_t>();
  unit_under_test_ = std::make_unique<ConcreteSPIInterface>();
  auto rv = unit_under_test_->Transfer(Tx, Rx);
  ASSERT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SpiInterfaceTests, write) {
  auto Tx = std::vector<std::uint8_t>();
  unit_under_test_ = std::make_unique<ConcreteSPIInterface>();
  auto rv = unit_under_test_->Write(Tx);
  ASSERT_EQ(rv, types::DriverStatus::OK);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}