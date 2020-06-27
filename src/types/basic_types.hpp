#ifndef SRC_TYPES_BASIC_TYPES_H_
#define SRC_TYPES_BASIC_TYPES_H_

#include <type_traits>

namespace types {

/**
 * @brief A 3 element type of variable datatype, which is meant to be used in the context of euclidean vectors
 * @tparam ElementType The underlying datatype of each of the three elements.
 *                     Underlying type needs to be arithmetic and trivial. 
 *                     It also needs to be signed in order to allow negative values.
 * 
 */
template <typename ElementType>
struct EuclideanVector {
  static_assert(std::is_arithmetic<ElementType>::value, "Type is not arithmetic");
  static_assert(std::is_trivial<ElementType>::value, "Type is not trivial");
  static_assert(std::is_signed<ElementType>::value, "Unsigned type can't be used");

  /// @brief  Default constructor is explicitly defaulted
  explicit EuclideanVector() = default;

  /// @brief Defaulted copy constructor
  EuclideanVector(const EuclideanVector& other) = default;

  /// @brief Defaulted move constructor
  EuclideanVector(EuclideanVector&& other) = default;

  /// @brief Custom constructor for all three elements
  explicit EuclideanVector(const ElementType x, const ElementType y, const ElementType z) : x(x), y(y), z(z){};

  /// X axis representation
  ElementType x;

  /// Y axis representation
  ElementType y;

  /// Z axis representation
  ElementType z;
};
}  // namespace types

#endif