#ifndef SRC_PROPULSION_LETODAR_2204
#define SRC_PROPULSION_LETODAR_2204

#include "motor.hpp"

namespace propulsion{
    
  class LeTodar2204 final: public Motor{
    public:
      LeTodar2204() = delete;
      explicit LeTodar2204(std::unique_ptr<Esc> esc): Motor(std::move(esc)){}

      auto GetCurrentSpeedInPercent() const noexcept -> const float override;
      auto SetSpeedInPercent(const float speed) noexcept -> types::InputError override;
  };
}

#endif