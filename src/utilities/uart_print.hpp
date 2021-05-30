#ifndef SRC_UTILITIES_UART_PRINT_HPP_
#define SRC_UTILITIES_UART_PRINT_HPP_

#include "stm32g4xx_hal.h"

#include <string>
#include <vector>
#include "serial_config.h"

namespace utilities {

auto UartPrint(std::string text) -> void;

}  // namespace utilities

#endif