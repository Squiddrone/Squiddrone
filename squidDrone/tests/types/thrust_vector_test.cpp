#include "gtest/gtest.h"
#include "basic_types.hpp"

/*
  static_assert will not be tested, because it is an compile time check
*/
namespace {
  
  TEST(thrust_vector_test, is_default_constructible) {
    types::ThrustVector<int> unit_under_test{};
    ASSERT_EQ(0, unit_under_test.x);
    ASSERT_EQ(0, unit_under_test.y);
    ASSERT_EQ(0, unit_under_test.z);
  }

  TEST(thrust_vector_test, is_copy_constructible){
    types::ThrustVector<int> other{1, 2, 3};
    types::ThrustVector<int> unit_under_test(other);
    ASSERT_EQ(1, unit_under_test.x);
    ASSERT_EQ(2, unit_under_test.y);
    ASSERT_EQ(3, unit_under_test.z);
  }

  TEST(thrust_vector_test, is_move_constructible){
    types::ThrustVector<long> other{3, 4, 5};
    types::ThrustVector<long> unit_under_test(std::move(other));
    ASSERT_EQ(3, unit_under_test.x);
    ASSERT_EQ(4, unit_under_test.y);
    ASSERT_EQ(5, unit_under_test.z);
  }
 
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}