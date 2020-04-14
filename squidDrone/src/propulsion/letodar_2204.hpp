#ifndef SRC_PROPULSION_LETODAR_2204
#define SRC_PROPULSION_LETODAR_2204

#include "motor.hpp"

namespace propulsion{
    
  class LeTodar2204 final: public Motor{
    public:
      LeTodar2204() = delete;
      explicit LeTodar2204(std::unique_ptr<Esc> esc): Motor(std::move(esc)), speed_(0.0){}

      auto GetCurrentSpeedInPercent() const noexcept -> const float override;
      auto SetSpeedInPercent(const float speed) noexcept -> types::InputError override;

    private:
      static constexpr int REPETITION_TIME_IN_MS = 500;
      static constexpr auto UPPER_LEGAL_RANGE_LIMIT_IN_PERCENT = 100.0;
      static constexpr auto LOWER_LEGAL_RANGE_LIMIT_IN_PERCENT = 0.0;
      static constexpr auto PERCENTAGE_FACTOR = 100.0;
      float speed_;
  };
}

#endif