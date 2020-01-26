#include "gtest/gtest.h"
#include "esc.hpp"
#include "stm32g4xx_hal_tim.h"


namespace{
  
  class ConcreteEsc: public propulsion::Esc{
    public:
      using propulsion::Esc::timer_;
      explicit ConcreteEsc(TIM_HandleTypeDef& timer): propulsion::Esc(timer) {}
  };

  TEST(esc_test, is_constructible_with_timer){
    TIM_HandleTypeDef mock_timer;
    mock_timer.test_member = 3;
    ConcreteEsc unit_under_test{mock_timer};
    ASSERT_EQ(mock_timer.test_member, unit_under_test.timer_.test_member);
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}