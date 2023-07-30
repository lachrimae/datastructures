#include "linkedlist.h"
#include "vector.h"

#include <optional>

#include "gtest/gtest.h"

namespace curran {

class LinkedListTest : public ::testing::Test {};

TEST_F(LinkedListTest, ConstructorDestructor) { LinkedList<int> list; }

TEST_F(LinkedListTest, CopyAndAssign) {
  LinkedList<int> list;
  list.push(1);
  list.push(2);
  LinkedList<int> list2(list);
  LinkedList<int> list3 = list;
  ASSERT_EQ(list.pop(), std::optional<int>(2));
  ASSERT_EQ(list.pop(), std::optional<int>(1));
  ASSERT_EQ(list2.pop(), std::optional<int>(2));
  ASSERT_EQ(list2.pop(), std::optional<int>(1));
  ASSERT_EQ(list3.pop(), std::optional<int>(2));
  ASSERT_EQ(list3.pop(), std::optional<int>(1));
}

TEST_F(LinkedListTest, PushAndPop) {
  LinkedList<int> list;
  list.push(1);
  std::optional<int> val = list.pop();
  ASSERT_EQ(val, std::optional<int>(1));
}

TEST_F(LinkedListTest, PushAndPopFront) {
  LinkedList<int> list;
  list.push_front(1);
  std::optional<int> val = list.pop_front();
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
    ASSERT_EQ(initial.value(), i);
  }
  ASSERT_EQ(list.pop_front(), std::optional<int>());
}

TEST_F(LinkedListTest, LargeExample) {
  LinkedList<int> list;
  for (int i = 0; i < 16384; i++) {
    list.push(i);
  }
  for (int i = 0; i < 16384; i++) {
    ASSERT_EQ(list[i], i);
  }
}

} // namespace curran
