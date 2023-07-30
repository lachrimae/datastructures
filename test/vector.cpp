#include "vector.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class VectorTest : public ::testing::Test {};

TEST_F(VectorTest, ConstructorDestructor) { Vector<int> vec; }

TEST_F(VectorTest, CopyAndAssign) {
  Vector<int> vec;
  vec.push(1);
  vec.push(2);
  Vector<int> vec2(vec);
  Vector<int> vec3 = vec;
  ASSERT_EQ(vec3.pop(), std::optional<int>(2));
  ASSERT_EQ(vec3.pop(), std::optional<int>(1));
  ASSERT_EQ(vec2.pop(), std::optional<int>(2));
  ASSERT_EQ(vec2.pop(), std::optional<int>(1));
  ASSERT_EQ(vec.pop(), std::optional<int>(2));
  ASSERT_EQ(vec.pop(), std::optional<int>(1));
}

TEST_F(VectorTest, PushWorks) {
  Vector<int> vec;
  vec.push(1);
  ASSERT_EQ(1, vec[0]);
}

TEST_F(VectorTest, PopWorks) {
  Vector<int> vec;
  vec.push(1);
  std::optional<int> val = vec.pop();
  ASSERT_EQ(std::optional<int>(1), val);
}

TEST_F(VectorTest, PopWorksWhenEmpty) {
  Vector<int> vec;
  std::optional<int> val = vec.pop();
  ASSERT_EQ(std::optional<int>(), val);
}

TEST_F(VectorTest, LargeExample) {
  Vector<int> vec;
  for (int i = 0; i < 1025; i++) {
    vec.push(i);
  }
  ASSERT_EQ(vec[512], 512);
  for (int i = 0; i < 1025; i++) {
    std::optional<int> last = vec.pop();
    ASSERT_EQ(last.value(), 1024 - i);
  }
}

} // namespace curran
