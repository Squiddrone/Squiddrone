#include "gtest/gtest.h"
#include "esc.hpp"
#include "stm32g4xx.h"


namespace{
  
  /// A mock implementation of the Esc class that should be tested here
  class ConcreteEsc final: public propulsion::Esc{
    public:
      using propulsion::Esc::timer_;
      explicit ConcreteEsc(TIM_HandleTypeDef* timer, std::uint32_t channel): propulsion::Esc(timer, channel) {}
 
      const auto GetMaxPulseDurationInMicroSeconds() const noexcept  -> int override{
        return max_pulse_;
      }

      const auto GetMinPulseDurationInMicroSeconds() const noexcept -> int override{
        return min_pulse_;
      }

      const auto SetPulseDuration(int pulse_duration, int repetition_period) noexcept -> decltype(types::HalError::WORKING){
        return types::HalError::PARAMETER_ERROR;
      }

    private:
      static constexpr auto max_pulse_ = 10;
      static constexpr auto min_pulse_ = 1;
  };

  std::uint32_t mock_channel = 2;

  TEST(esc_test, is_constructible_with_timer){
    TIM_HandleTypeDef mock_timer;
    mock_timer.test_member = 3;
    ConcreteEsc unit_under_test{&mock_timer, mock_channel};
    ASSERT_EQ(mock_timer.test_member, unit_under_test.timer_->test_member);
  }

  TEST(esc_test, get_max_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{&mock_timer, mock_channel};
    ASSERT_EQ(10, unit_under_test.GetMaxPulseDurationInMicroSeconds());
  }

  TEST(esc_test, get_min_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{&mock_timer, mock_channel};
    ASSERT_EQ(1, unit_under_test.GetMinPulseDurationInMicroSeconds());
  }

  TEST(esc_test, set_pulse_duration){
    TIM_HandleTypeDef mock_timer;
    ConcreteEsc unit_under_test{&mock_timer, mock_channel};
    ASSERT_EQ(types::HalError::PARAMETER_ERROR, unit_under_test.SetPulseDuration(1,1));
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}