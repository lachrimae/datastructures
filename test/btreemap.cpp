#include "btreemap.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class BTreeMapTest : public ::testing::Test {};

TEST_F(BTreeMapTest, ConstructDestruct) { BTreeMap<int, int> h; }

TEST_F(BTreeMapTest, HasItem) {
  BTreeMap<int, int> h;
  h.set(0, 1);
  ASSERT_EQ(h.has(0), true);
}

TEST_F(BTreeMapTest, SetGetDelete) {
  BTreeMap<int, int> h;
  ASSERT_EQ(h.get(0), std::optional<int>());
  h.set(0, 1);
  ASSERT_EQ(h.get(0), std::optional<int>(1));
  h.set(0, 2);
  ASSERT_EQ(h.get(0), std::optional<int>(2));
  h.del(0);
  ASSERT_EQ(h.get(0), std::optional<int>());
  h.set(0, 3);
  ASSERT_EQ(h.get(0), std::optional<int>(3));
}

TEST_F(BTreeMapTest, LargeExample) {
  BTreeMap<int, int> h;
  for (int i = 0; i < 1024; i++) {
    h.set(i, i);
  }
  for (int i = 0; i < 1024; i++) {
    ASSERT_EQ(h.get(i), std::optional<int>(i));
    h.del(i);
  }
}

} // namespace curran
