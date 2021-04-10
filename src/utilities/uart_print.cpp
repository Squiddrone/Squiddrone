
#include "uart_print.hpp"

namespace utilities {

auto UartPrint(std::string text) -> void {
  text = text + "\r\n";
  auto uchar_vector = std::vector<unsigned char>(text.data(), text.data() + text.length());
  HAL_UART_Transmit(&huart2, uchar_vector.data(), (uint16_t)text.length(), HAL_MAX_DELAY);
}

}  // namespace utilities