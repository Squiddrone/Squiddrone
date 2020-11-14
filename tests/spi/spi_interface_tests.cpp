#include "gtest/gtest.h"
#include "spi_interface.hpp"

namespace {
class ConcreteSPIInterface final : public spi::SPIInterface {
 public:
  explicit ConcreteSPIInterface() : spi::SPIInterface(){};
  auto Transfer(std::vector<std::uint8_t> &RxData, std::vector<std::uint8_t> &TxData) noexcept -> types::SPIStatus override {
    return types::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
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
  auto rv = unit_under_test_->Transfer(Rx, Tx);
  ASSERT_EQ(rv, types::SPIStatus::SPI_TRANSACTION_SUCCESSFUL);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}