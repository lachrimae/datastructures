#include "hashmap.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class HashMapTest : public ::testing::Test {};

TEST_F(HashMapTest, ConstructDestruct) { HashMap<int, int> h; }

TEST_F(HashMapTest, HasItem) {
  HashMap<int, int> h;
  h.set(0, 1);
  ASSERT_EQ(h.has(0), true);
}

TEST_F(HashMapTest, SetGetDelete) {
  HashMap<int, int> h;
  ASSERT_EQ(h.get(0), std::optional<int>());
  h.set(0, 1);
  ASSERT_EQ(h.get(0), std::optional<int>(1));
  h.set(0, 2);
  ASSERT_EQ(h.get(0), std::optional<int>(2));
  h.set(0, 2);
  ASSERT_EQ(h.get(0), std::optional<int>(2));
  h.del(0);
  ASSERT_EQ(h.get(0), std::optional<int>());
  h.set(0, 3);
  ASSERT_EQ(h.get(0), std::optional<int>(3));
}

TEST_F(HashMapTest, MoreValsThanBuckets) {
  HashMap<int, int> h(8);
  for (int i = 0; i < 1024; i++) {
    h.set(i, i);
  }
  for (int i = 0; i < 1024; i++) {
    ASSERT_EQ(h.get(i), std::optional<int>(i));
    h.del(i);
  }
}

} // namespace curran
