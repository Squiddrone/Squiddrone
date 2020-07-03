#ifndef SRC_GLOBALS_HPP
#define SRC_GLOBALS_HPP

#ifdef STM32G431xx
static constexpr auto MCU_CLOCK = 170000000;  //Hertz
///currently MCU_CLOCK is not divided to get ESC_TIMER
static constexpr auto TIMER_CLOCK = MCU_CLOCK;
#else
#error "MCU is not known, define MCU"
#endif

#endif