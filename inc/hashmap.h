#pragma once
#include "linkedlist.h"
#include "vector.h"
#include <optional>
#include <utility>

namespace curran {

constexpr unsigned long int fnv_offset_basis = 0xcbf29ce484222325;
constexpr unsigned long int fnv_prime = 0x00000100000001B3;

// Fowler–Noll–Vo hash function
template <typename T> unsigned long int hash(T *data) {
  unsigned long int result = fnv_offset_basis;
  size_t len = sizeof(T);
  for (size_t i = 0; i < len; i++) {
    result *= fnv_prime;
    result ^= ((char *)data)[i];
  }
  return result;
}

template <typename Key, typename Val> class HashMap {
public:
  HashMap();
  HashMap(size_t capacity);
  void set(Key key, Val val);
  std::optional<Val> get(Key key);
  void del(Key key);
  bool has(Key key);

private:
  Vector<LinkedList<std::pair<Key, Val>> *> entries;
  constexpr LinkedList<std::pair<Key, Val>> &at_index(size_t index);
};

template <typename Key, typename Val> inline HashMap<Key, Val>::HashMap() {
  Vector<LinkedList<std::pair<Key, Val>> *> entries;
}

template <typename Key, typename Val>
inline HashMap<Key, Val>::HashMap(size_t capacity) {
  Vector<LinkedList<std::pair<Key, Val>> *> entries(capacity);
}

template <typename Key, typename Val>
inline void HashMap<Key, Val>::set(Key key, Val val) {
  unsigned long int index = hash<Key>(&key);
  entries[index]->push(std::pair<Key, Val>(key, val));
}

template <typename Key, typename Val>
constexpr inline LinkedList<std::pair<Key, Val>> &
HashMap<Key, Val>::at_index(size_t index) {
  return entries[index];
}

template <typename Key, typename Val>
inline std::optional<Val> HashMap<Key, Val>::get(Key key) {
  unsigned long int index = hash<Key>(&key);
  if (entries[index]->length() <= 0) {
    return std::optional<Val>();
  } else {
    for (size_t i = 0; i < entries[index]->length(); i++) {
      if (key == at_index(index)[i].first)
        return std::optional<Val>(at_index(index)[i].second);
    }
    return std::optional<Val>();
  }
}

template <typename Key, typename Val> void HashMap<Key, Val>::del(Key key) {
  unsigned long int index = hash<Key>(&key);
  for (size_t i = 0; i < entries[index]->length(); i++) {
    if (key == at_index(index)[i].first)
      entries[index]->del(i);
    return;
  }
}
}

template <typename Key, typename Val> bool HashMap<Key, Val>::has(Key key) {
  unsigned long int index = hash<Key>(&key);
  for (size_t i = 0; i < entries[index]->length(); i++) {
    if (key == at_index(index)[i].first)
      return true;
  }
}
return false;
}

} // namespace curran
