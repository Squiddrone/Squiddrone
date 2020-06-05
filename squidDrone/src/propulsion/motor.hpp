#ifndef SRC_PROPULSION_MOTOR_HPP
#define SRC_PROPULSION_MOTOR_HPP

#include <memory>
#include "error_types.hpp"

///needed for swapping header in unittesting
#ifndef UNIT_TEST
#include "esc.hpp"
#else
#include "esc_mock.hpp"
#endif

namespace propulsion{
    
  /**
   * @brief This abstract class is the interface for implementing
   * specific motor types 
   * 
   */
  class Motor{
    public:
      /**
       * @brief Default constructor not needed
       * 
       */
      Motor() = delete;

      /** 
       * @brief This custom ctor is the only one to be used
       * @param esc A unique_ptr to the abstract base class of 
       *            all ESCs. The inheriting class should be 
       *            intialized with a specialized ESC casted to 
       *            to the ESC base class
       * 
       */
      explicit Motor(std::unique_ptr<Esc> esc): esc_(std::move(esc)){}

      /**
       * @brief Default behavior of Motor dtor is sufficent, because
       *        unique_ptr gets deleted if it goes out of scope
       * 
       */
      virtual ~Motor() = default;

      /**
       * @brief Returns the current speed of the motor converted to 
       *        percent
       * @return Current speed in percent between 0 and 100
       * 
       */
      virtual auto GetCurrentSpeedInPercent() const noexcept -> const float = 0;

      /**
       * @brief Handles setting rotational speed of the motor via the Esc
       * @param speed Speed in percent that should be reached by this motor
       * @return A types::InputError to indicate whether it is faulty or not
       * 
       */
      virtual auto SetSpeedInPercent(const float speed) noexcept -> types::InputError = 0;
  
    protected:
      /// Holds the local reference to a concrete ESC object
      std::unique_ptr<Esc> esc_;
  };
}



#endif