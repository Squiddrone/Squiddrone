#include "gtest/gtest.h"
#include "spi_interface.hpp"

namespace {
  class ConcreteSPIInterface final: public spi::SPIInterface {
    public:
      explicit ConcreteSPIInterface() : spi::SPIInterface(){};
      auto Transfer(std::unique_ptr<std::uint8_t> RxData, std::unique_ptr<std::uint8_t> TxData) noexcept -> spi::SPIStatus override{
        return spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL;
      };
  };

  class SpiInterfaceTests : public ::testing::Test {
    protected:
      std::unique_ptr<ConcreteSPIInterface> unit_under_test_;
  };

  TEST_F(SpiInterfaceTests, transfer){
    auto Rx = std::make_unique<std::uint8_t>();
    auto Tx = std::make_unique<std::uint8_t>();
    unit_under_test_ = std::make_unique<ConcreteSPIInterface>();
    auto rv = unit_under_test_->Transfer(std::move(Rx), std::move(Tx));
    ASSERT_EQ(rv, spi::SPIStatus::SPI_TRANSACTION_SUCCESSFUL);
  }
}

int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}