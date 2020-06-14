#include <utility>
#include "gtest/gtest.h"
#include "letodar_2204.hpp"

namespace{
  class Letodar2204Tests: public ::testing::Test{
    protected:
      virtual void SetUp(){
        unit_under_test_ = std::make_unique<propulsion::LeTodar2204>(std::make_unique<propulsion::Esc>(esc_));
      }

      virtual void SetUpWithReturnTypeForSetPulseDuration(types::HalError provoked_error){
        propulsion::Esc new_esc;
        new_esc.set_pulse_duration_return_value_ = provoked_error;
        unit_under_test_ = std::make_unique<propulsion::LeTodar2204>(std::make_unique<propulsion::Esc>(new_esc));
      }

      propulsion::Esc esc_;
      std::unique_ptr<propulsion::LeTodar2204> unit_under_test_;
  };

  TEST_F(Letodar2204Tests, get_current_speed_in_percent_works){
    auto current_speed = unit_under_test_->GetCurrentSpeedInPercent();
    ASSERT_FLOAT_EQ(0.0, current_speed);
  }

  TEST_F(Letodar2204Tests, set_speed_in_percent_lower_illegal_bounds){
    auto set_speed_return = unit_under_test_->SetSpeedInPercent(-1.0);
    ASSERT_EQ(types::InputError::INPUT_OUT_OF_RANGE, set_speed_return);
  }

  TEST_F(Letodar2204Tests, set_speed_in_percent_upper_illegal_bounds){
    auto set_speed_return = unit_under_test_->SetSpeedInPercent(100.1);
    ASSERT_EQ(types::InputError::INPUT_OUT_OF_RANGE, set_speed_return);
  }

  TEST_F(Letodar2204Tests, set_speed_in_percent_legal_range){
    auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
    ASSERT_EQ(types::InputError::INPUT_CORRECT, set_speed_return);
  }

  TEST_F(Letodar2204Tests, set_speed_in_percent_hal_error_triggered){
    SetUpWithReturnTypeForSetPulseDuration(types::HalError::CONFIG_ERROR);
    auto set_speed_return = unit_under_test_->SetSpeedInPercent(50.0);
    ASSERT_EQ(types::InputError::INPUT_FAULTY, set_speed_return);
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}