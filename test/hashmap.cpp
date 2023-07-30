#include "hashmap.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class HashMapTest : public ::testing::Test {};

TEST_F(HashMapTest, ConstructDestruct) {
    HashMap<int, int> h;
}

TEST_F(HashMapTest, HasItem) {
    HashMap<int, int> h;
    h.set(0, 1);
    ASSERT_EQ(h.has(0), true);
}

} // namespace curran
