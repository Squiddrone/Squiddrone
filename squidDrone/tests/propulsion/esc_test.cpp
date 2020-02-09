#include "gtest/gtest.h"
#include "esc.hpp"
#include "stm32g4xx.h"


namespace{
  
  /// A mock implementation of the Esc class that should be tested here
  class ConcreteEsc: public propulsion::Esc{
    public:
      using propulsion::Esc::timer_;
      explicit ConcreteEsc(TIM_HandleTypeDef& timer): propulsion::Esc(timer) {}
 
      const auto GetMaxPulseDurationInMicroSeconds() const noexcept  -> decltype(auto){
        return max_pulse_;
      }

      const auto GetMinPulseDurationInMicroSeconds() const noexcept -> decltype(auto){
        return min_pulse_;
      }

      const auto SetPulseDuration(int pulse_duration) noexcept -> decltype(types::HalError::working){
        return types::HalError::parameter_change_error;
      }

    private:
      static constexpr auto max_pulse_ = 10;
      static constexpr auto min_pulse_ = 1;
  };

  TEST(esc_test, is_constructible_with_timer){
    TIM_HandleTypeDef mock_timer;
    mock_timer.test_member = 3;
    ConcreteEsc unit_under_test{mock_timer};
    ASSERT_EQ(mock_timer.test_member, unit_under_test.timer_.test_member);
  }

  TEST(esc_test, get_max_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{mock_timer};
    ASSERT_EQ(10, unit_under_test.GetMaxPulseDurationInMicroSeconds());
  }

  TEST(esc_test, get_min_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{mock_timer};
    ASSERT_EQ(1, unit_under_test.GetMinPulseDurationInMicroSeconds());
  }

  TEST(esc_test, set_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{mock_timer};
    ASSERT_EQ(types::HalError::parameter_change_error, unit_under_test.SetPulseDuration(1));
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}