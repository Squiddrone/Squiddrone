#ifndef TESTS_MOCK_LIBRARIES_PROPULSION_MOTOR_MOCK_HPP_
#define TESTS_MOCK_LIBRARIES_PROPULSION_MOTOR_MOCK_HPP_


#include <memory>
#include "esc_mock.hpp"

namespace propulsion{
  class Motor{
    public:
      Motor(std::unique_ptr<Esc> esc): esc_{std::move(esc)}{} 
      std::unique_ptr<Esc> esc_;
  };
}

#endif