#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#define TESTS_MOCK_LIBRARIES_PROPULSION_ESC_MOCK_HPP
#include "error_types.hpp"
#include "esc.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockEsc : public propulsion::Esc {
 public:
  MockEsc() : Esc(nullptr, 0) {}
  MockEsc(const MockEsc&) : Esc(nullptr, 0) {}
  MockEsc(TIM_HandleTypeDef* timer, std::uint32_t channel) : Esc(nullptr, 0) {}
  MOCK_METHOD(const int, GetMaxPulseDurationInMicroSeconds, (), (const, noexcept, override));
  MOCK_METHOD(const int, GetMinPulseDurationInMicroSeconds, (), (const, noexcept, override));
  MOCK_METHOD(const types::DriverStatus, SetPulseDuration, (const float pulse_duration, int repetition_period), (noexcept, override));
};

#endif