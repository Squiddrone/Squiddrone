#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_LETODAR_2204_MOCK_HPP_

#include <memory>
#include "motor_mock.hpp"
#include "little_bee_20_a_mock.hpp"

namespace propulsion
{
  class LeTodar2204: public Motor{
    public:
    LeTodar2204(std::unique_ptr<Esc> esc):Motor{std::move(esc)}{}
    auto GetCurrentSpeedInPercent() const noexcept -> const float{
      return 1.0;
    }
    virtual auto SetSpeedInPercent(const float speed) noexcept -> types::InputError{
      return types::InputError::INPUT_CORRECT;
    }
  };
} 

#endif