#include "vector.h"

#include <iostream>
#include <optional>

#include "gtest/gtest.h"

namespace curran {

class VectorTest : public ::testing::Test {};

} // namespace curran

// int main(int argc, char **argv) {
//   Vector<int> vec;
//   vec.push(1);
//   assert(vec[0] == 1, "First entry was not 1");
//   std::optional<int> initial = vec.pop();
//   assert(initial.value() == 1, "Popped first entry was not 1");
//   std::optional<int> nonexistent = vec.pop();
//   assert(!nonexistent.has_value(), "Nonexistent pop had entry after all");
// 
//   for (int i = 0; i < 1024; i++) {
//     vec.push(i);
//   }
//   for (int i = 0; i < 1024; i++) {
//     std::optional<int> last = vec.pop();
//     assert(last.value() == 1023 - i, "Popped first entry was not i");
//   }
// 
//   std::cout << "All tests passed." << std::endl;
//   return 0;
// }
