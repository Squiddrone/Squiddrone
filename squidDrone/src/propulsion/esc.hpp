#ifndef SRC_PROPULSION_ESC_HPP_
#define SRC_PROPULSION_ESC_HPP_

#include "stm32g4xx_hal_tim.h"

class Esc{
  public:
    explicit Esc() = default;
    explicit Esc(TIM_HandleTypeDef timer): timer_(timer){};

  protected:
    TIM_HandleTypeDef timer_;
};  








#endif