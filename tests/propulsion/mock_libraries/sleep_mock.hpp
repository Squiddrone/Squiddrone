
#ifndef TESTS_PROPULSION_MOCK_LIBRARIES_SLEEP_MOCK_HPP_
#define TESTS_PROPULSION_MOCK_LIBRARIES_SLEEP_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace utilities {

auto Sleep(uint32_t sleep_time_in_ms) noexcept -> void;

}  // namespace utilities

#endif