#ifndef TESTS_COM_MOCK_LIBRARIES_UART_PRINT_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_UART_PRINT_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace utilities {

auto UartPrint(std::string text) -> void;

}  // namespace utilities

#endif