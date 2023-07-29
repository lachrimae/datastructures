#include "linkedlist.h"
#include "vector.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class LinkedListTest : public ::testing::Test {};

TEST_F(LinkedListTest, PushAndPop) {
    LinkedList<int> list;
    list.push(1);
    std::optional<int> val = list.pop();
    ASSERT_EQ(val, std::optional<int>(1));
}

TEST_F(LinkedListTest, VectorInitializer) {
    Vector<int> vec;
    for (int i = 0; i < 16; i++) {
        vec.push(i);
    }
    LinkedList<int> list(vec);
    for (int i = 0; i < 16; i++) {
        std::optional<int> initial = list.pop_front();
        ASSERT_EQ(initial.value(),  i);
    }
    ASSERT_EQ(list.pop_front(), std::optional<int>());
}

} // namespace curran
