#include "gtest/gtest.h"
#include "basic_types.hpp"

/*
  static_assert will not be tested, because it is an compile time check
*/
namespace {
  
  TEST(euclidean_vector_test, is_default_constructible) {
    types::EuclideanVector<int> unit_under_test{};
    ASSERT_EQ(0, unit_under_test.x);
    ASSERT_EQ(0, unit_under_test.y);
    ASSERT_EQ(0, unit_under_test.z);
  }

  TEST(euclidean_vector_test, is_copy_constructible){
    types::EuclideanVector<float> other{1.5, 2.5, 3.5};
    types::EuclideanVector<float> unit_under_test(other);
    ASSERT_EQ(1.5, unit_under_test.x);
    ASSERT_EQ(2.5, unit_under_test.y);
    ASSERT_EQ(3.5, unit_under_test.z);
  }

  TEST(euclidean_vector_test, is_move_constructible){
    types::EuclideanVector<long> other{3, 4, 5};
    types::EuclideanVector<long> unit_under_test(std::move(other));
    ASSERT_EQ(3, unit_under_test.x);
    ASSERT_EQ(4, unit_under_test.y);
    ASSERT_EQ(5, unit_under_test.z);
  }
 
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}