#pragma once
#include <optional>

namespace curran {
template <typename Key, typename Val> class Hashmap {
public:
  Hashmap();
  void set(Key key, Val val);
  std::optional<Val> get(Key key);
  void del(Key key);
  bool has(Key key);
private:

};
} // namespace curran
