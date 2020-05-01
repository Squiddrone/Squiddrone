#ifndef SRC_PROPULSION_LETODAR_2204
#define SRC_PROPULSION_LETODAR_2204

#include "motor.hpp"

namespace propulsion{
  
  /**
  * @class LeTodar2204
  * @brief The concrete implementation of the LeTodar2204 Motor
  */
  class LeTodar2204 final: public Motor{
    public:
      /**
      * @brief Default ctor not needed
      */
      LeTodar2204() = delete;
      
      /**
      * @brief Custom ctor by using a pointer to a concrete Esc, identified by its abstract interface
      * @param esc A unique pointer to a instance of a ESC
      */
      explicit LeTodar2204(std::unique_ptr<Esc> esc): Motor(std::move(esc)), speed_(0.0){}

      /**
      * @brief Returns the last known speed in percent
      */
      auto GetCurrentSpeedInPercent() const noexcept -> const float override;

      /**
      * @brief Sets the speed to the ESC based on the values configured there
      * @param speed The speed to be set (between 0.0 and 100.0)
      * @return types::InputError::INPUT_CORRECT if everything is working fine.
      *         types::InputError::INPUT_OUT_OF_RANGE if speed exceeds lower and upper limits
      *         types::InputError::INPUT_FAULTY if input caused the HAL to fail and throw an error.
      */
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