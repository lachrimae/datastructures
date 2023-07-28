#include "vector.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class VectorTest : public ::testing::Test {};

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

TEST_F(VectorTest, LargeExampleNoCrash) {
  Vector<int> vec;
  for (int i = 0; i < 1025; i++) {
    vec.push(i);
  }
  for (int i = 0; i < 1025; i++) {
    std::optional<int> last = vec.pop();
    ASSERT_EQ(last.value(), 1024 - i);
  }
}

} // namespace curran
