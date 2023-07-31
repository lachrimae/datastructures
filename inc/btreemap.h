#pragma once

#include <functional>
#include <optional>
#include <stdexcept>

namespace curran {

// We use 3-trees here.

template <typename Key, typename Val> struct Node {
  Key key;
  Val *val;
  Node<Key, Val> *parent;
  Node<Key, Val> *left_child;
  Node<Key, Val> *centre_child;
  Node<Key, Val> *right_child;
  bool full() { return left_child && centre_child && right_child; }
};

template <typename Key, typename Val> class BTreeMap {
public:
  BTreeMap();
  BTreeMap(std::function<char(Key, Key)> comparator);
  void set(Key key, Val val);
  std::optional<Val> get(Key key);
  void del(Key key);
  bool has(Key key);

private:
  Node<Key, Val> *root;
  std::optional<std::function<char(Key, Key)>> comparator;
  char comparator_(Key a, Key b);
};

template <typename Key, typename Val>
inline BTreeMap<Key, Val>::BTreeMap()
    : root(NULL), comparator(std::optional<std::function<char(Key, Key)>>()) {}

template <typename Key, typename Val>
inline BTreeMap<Key, Val>::BTreeMap(std::function<char(Key, Key)> comparator)
    : root(NULL),
      comparator(std::optional<std::function<char(Key, Key)>>(comparator)) {}

template <typename Key, typename Val>
inline char BTreeMap<Key, Val>::comparator_(Key a, Key b) {
  if (comparator.has_value()) {
    return comparator.value()(a, b);
  }
  if (a < b) {
    return -1;
  } else if (a == b) {
    return 0;
  } else {
    return 1;
  }
}

template <typename Key, typename Val>
inline void BTreeMap<Key, Val>::set(Key key, Val val) {
  Node<Key, Val> *new_node = new Node<Key, Val>;
  {
    Val *val_ptr = new Val(val);
    new_node->parent = NULL;
    new_node->left_child = NULL;
    new_node->centre_child = NULL;
    new_node->right_child = NULL;
    new_node->key = key;
    new_node->val = val_ptr;
  }

  if (!root) {
    root = new_node;
    return;
  }
  Node<Key, Val> *current = root;
  while (true) {
    char diff_with_left = comparator_(key, current->left_child->key);
    if (diff_with_left < 0) {
      if (current->full()) {
        current = current->left_child;
        continue;
      }
      current->right_child = current->centre_child;
      current->centre_child = current->left_child;
      current->left_child = new_node;
      return;
    } else if (diff_with_left == 0) {
      Node<Key, Val> *delete_me = current->left_child;
      current->left_child = new_node;
      delete delete_me->val;
      delete delete_me;
      return;
    }
    if (!current->centre_child) {
      current->centre_child = new_node;
      return;
    }
    char diff_with_centre = comparator_(key, current->centre_child->key);
    if (diff_with_centre < 0) {
      if (current->full()) {
        // TODO
      }
      current->right_child = current->centre_child;
      current->centre_child = new_node;
      return;
    } else if (diff_with_centre == 0) {
      Node<Key, Val> *delete_me = current->centre_child;
      current->centre_child = new_node;
      delete delete_me->val;
      delete delete_me;
      return;
    } else {
      current->right_child = new_node;
      return;
    }
    throw std::logic_error("Inexhaustive cases");
  }
}

} // namespace curran
