#ifndef SRC_TYPES_BASIC_TYPES_H_
#define SRC_TYPES_BASIC_TYPES_H_

#include<type_traits>

namespace types{

  ///
  /// @brief A 3 element type of variable datatype, which is meant to be used in the context of thrust
  /// @tparam ElementType The underlying datatype of each of the three elements.
  ///                     Underlying type needs to be arithmetic and trivial. 
  ///                     It also needs to be signed in order to allow negative thrust.
  ///
  template<typename ElementType>
  struct ThrustVector
  {
    static_assert(std::is_arithmetic<ElementType>::value, "Type is not arithmetic");
    static_assert(std::is_trivial<ElementType>::value, "Type is not trivial");
    static_assert(std::is_signed<ElementType>::value, "Unsigned type can't be used");
    explicit ThrustVector() = default;
    explicit ThrustVector(const ThrustVector& other) = default;
    explicit ThrustVector(ThrustVector&& other) = default;
    explicit ThrustVector(const ElementType x, const ElementType y, const ElementType z): x(x), y(y), z(z){};
    ElementType x;
    ElementType y;
    ElementType z;
  };
}



#endif