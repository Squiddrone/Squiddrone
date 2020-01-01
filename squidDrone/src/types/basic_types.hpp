#ifndef SRC_TYPES_BASIC_TYPES_H_
#define SRC_TYPES_BASIC_TYPES_H_


#include<cstdint>
#include<type_traits>

namespace types{

  template<typename ElementType>
  struct ThrustVector
  {
    static_assert(std::is_integral<ElementType>::value, "Type is not integral");
    static_assert(std::is_trivial<ElementType>::value, "Type is not trivial");
    static_assert(std::is_signed<ElementType>::value, "Unsigned Type can't be used");
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