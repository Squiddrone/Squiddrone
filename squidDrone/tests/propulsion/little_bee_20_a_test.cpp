#include <memory>
#include <utility>
#include "gtest/gtest.h"
#include "little_bee_20_a.hpp"
#include "stm32g4xx.h"

namespace{

  class LittleBeeEscTests: public ::testing::Test{
    protected:
      virtual void SetUp(){
        unit_under_test_ = std::make_unique<propulsion::LittleBee20A>(&mock_timer);
      }

      TIM_HandleTypeDef mock_timer;
      std::unique_ptr<propulsion::LittleBee20A> unit_under_test_;
  };

  TEST_F(LittleBeeEscTests, get_max_pulse_duration_in_micro_seconds_return_correct_value){
    ASSERT_EQ(unit_under_test_->GetMaxPulseDurationInMicroSeconds(), 250);
  }

  TEST_F(LittleBeeEscTests, get_min_pulse_duration_in_micro_seconds_return_correct_value){
    ASSERT_EQ(unit_under_test_->GetMinPulseDurationInMicroSeconds(), 125);
  }

  


}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}