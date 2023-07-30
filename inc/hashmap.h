#pragma once
#include "linkedlist.h"
#include "vector.h"
#include <optional>
#include <utility>

namespace curran {

constexpr size_t default_entries_len__ = 512;
constexpr unsigned long int fnv_offset_basis__ = 0xcbf29ce484222325;
constexpr unsigned long int fnv_prime__ = 0x00000100000001B3;

// Fowler–Noll–Vo hash function
template <typename T> unsigned long int hash(T *data) {
  unsigned long int result = fnv_offset_basis__;
  size_t len = sizeof(T);
  for (size_t i = 0; i < len; i++) {
    result *= fnv_prime__;
    result ^= ((char *)data)[i];
  }
  return result;
}

template <typename Key, typename Val> class HashMap {
public:
  HashMap();
  HashMap(size_t capacity);
  ~HashMap();
  void set(Key key, Val val);
  std::optional<Val> get(Key key);
  void del(Key key);
  bool has(Key key);

private:
  Vector<LinkedList<std::pair<Key, Val>> *> entries;
  constexpr LinkedList<std::pair<Key, Val>> &at_index(size_t index);
  unsigned long int hash_key(Key &key);
};

template <typename Key, typename Val>
inline unsigned long int HashMap<Key, Val>::hash_key(Key &key) {
  unsigned long int raw_hash = hash<Key>(&key);
  return raw_hash % entries.length();
}

template <typename Key, typename Val>
inline HashMap<Key, Val>::HashMap() : HashMap(default_entries_len__) {}

template <typename Key, typename Val>
inline HashMap<Key, Val>::HashMap(size_t capacity) : entries(capacity) {
  for (size_t i = 0; i < capacity; i++) {
    LinkedList<std::pair<Key, Val>> *ll = new LinkedList<std::pair<Key, Val>>;
    entries.push(ll);
  }
}

template <typename Key, typename Val> inline HashMap<Key, Val>::~HashMap() {
  for (size_t i = 0; i < entries.length(); i++) {
    delete entries[i];
  }
}

template <typename Key, typename Val>
inline void HashMap<Key, Val>::set(Key key, Val val) {
  unsigned long int index = hash_key(key);
  entries[index]->push(std::pair<Key, Val>(key, val));
}

template <typename Key, typename Val>
constexpr inline LinkedList<std::pair<Key, Val>> &
HashMap<Key, Val>::at_index(size_t index) {
  return *entries[index];
}

template <typename Key, typename Val>
inline std::optional<Val> HashMap<Key, Val>::get(Key key) {
  unsigned long int index = hash_key(key);
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
  unsigned long int index = hash_key(key);
  for (size_t i = 0; i < entries[index]->length(); i++) {
    if (key == at_index(index)[i].first)
      entries[index]->del(i);
    return;
  }
}

template <typename Key, typename Val> bool HashMap<Key, Val>::has(Key key) {
  unsigned long int index = hash_key(key);
  for (size_t i = 0; i < entries[index]->length(); i++) {
    if (key == at_index(index)[i].first)
      return true;
  }
  return false;
}

} // namespace curran
