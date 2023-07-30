#pragma once
#include <optional>
#include <stdexcept>
#include <utility>

#include "common.h"
#include "vector.h"

namespace curran {

template <typename T> struct Node {
  Node<T> *prev;
  Node<T> *next;
  T *val;
};

template <typename T> class LinkedList {
private:
  Node<T> *initial;
  Node<T> *terminal;
  size_t length_;
  void insert_from_rear(size_t index, T val);
  void insert_from_front(size_t index, T val);
  void del_from_front(size_t index);
  void del_from_rear(size_t index);

public:
  LinkedList();
  LinkedList(Vector<T> &vec);
  LinkedList(const LinkedList<T> &);
  LinkedList<T> &operator=(const LinkedList<T> &other);
  ~LinkedList();
  void push(const T &val);
  std::optional<T> pop();
  void push_front(const T &val);
  std::optional<T> pop_front();
  void insert(size_t index, T val);
  T &operator[](size_t index);
  const T &operator[](size_t index) const;
  void del(size_t index);
  size_t length();
};

template <typename T> inline LinkedList<T>::LinkedList() {
  this->initial = NULL;
  this->terminal = NULL;
  this->length_ = 0;
}

template <typename T>
inline LinkedList<T>::LinkedList(Vector<T> &vec) : LinkedList() {
  while (true) {
    std::optional<T> val = vec.pop();
    if (!val.has_value()) {
      break;
    }
    push_front(val.value());
  }
}

template <typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T> &other) : LinkedList() {
  for (size_t i = 0; i < other.length_; i++) {
    push(other[i]);
  }
}

template <typename T>
inline LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
  if (this != &other) {
    for (size_t i = 0; i < other.length_; i++) {
      if (i < length_) {
        (*this)[i] = other[i];
      } else {
        push(other[i]);
      }
    }
  }
  return this;
}

template <typename T> inline LinkedList<T>::~LinkedList() {
  Node<T> *current = this->initial;
  while (current) {
    Node<T> *next = current->next;
    delete current->val;
    delete current;
    current = next;
  }
}

template <typename T> inline void LinkedList<T>::push(const T &val) {
  Node<T> *node = new Node<T>;
  node->prev = this->terminal;
  node->next = NULL;
  T *val_ptr = new T;
  *val_ptr = val;
  node->val = val_ptr;
  if (this->terminal) {
    this->terminal->next = node;
  } else {
    this->initial = node;
  }
  this->terminal = node;
  this->length_++;
}

template <typename T> inline std::optional<T> LinkedList<T>::pop() {
  if (this->length_ <= 0) {
    return std::optional<T>();
  }
  Node<T> *terminal = this->terminal;
  T val = *terminal->val;
  delete terminal->val;
  if (this->initial == terminal) {
    this->initial = NULL;
  }
  this->terminal = terminal->prev;
  this->length_--;
  delete terminal;
  return std::optional(val);
}

template <typename T> inline void LinkedList<T>::push_front(const T &val) {
  Node<T> *node = new Node<T>;
  node->prev = NULL;
  node->next = this->initial;
  T *val_ptr = new T;
  *val_ptr = val;
  node->val = val_ptr;
  if (this->initial) {
    this->initial->prev = node;
  } else {
    this->terminal = node;
  }
  this->initial = node;
  this->length_++;
}

template <typename T> inline std::optional<T> LinkedList<T>::pop_front() {
  if (this->length_ <= 0) {
    return std::optional<T>();
  }
  Node<T> *initial = this->initial;
  T val = *initial->val;
  delete initial->val;
  this->initial = initial->next;
  this->length_--;
  if (length_ == 0) {
    this->terminal = NULL;
  }
  delete initial;
  return std::optional(val);
}

template <typename T> inline void LinkedList<T>::insert(size_t index, T val) {
  if (index == 0) {
    this->push_front(val);
    return;
  } else if (index == this->length_) {
    this->push(val);
    return;
  } else if (index > this->length_ || index < 0) {
    throw std::out_of_range("LinkedList<T>::insert: index out of range");
  }
  if (index * 2 > this->length_) {
    this->insert_from_rear(index, val);
  } else {
    this->insert_from_front(index, val);
  }
}

template <typename T> inline T &LinkedList<T>::operator[](size_t index) {
  return const_cast<T &>(std::as_const(*this)[index]);
}

template <typename T>
inline const T &LinkedList<T>::operator[](size_t index) const {
  if (index >= length_) {
    throw std::out_of_range("LinkedList<T>::operator[]: index out of range");
  }
  size_t current_index = 0;
  const Node<T> *current = initial;
  while (current_index < index) {
    current = current->next;
    current_index++;
  }
  return *current->val;
}

template <typename T>
inline void LinkedList<T>::insert_from_front(size_t index, T val) {
  throw NotImplemented();
}

template <typename T>
inline void LinkedList<T>::insert_from_rear(size_t index, T val) {
  throw NotImplemented();
}

template <typename T> inline void LinkedList<T>::del(size_t index) {
  throw NotImplemented();
}

template <typename T> inline void LinkedList<T>::del_from_front(size_t index) {
  throw NotImplemented();
}

template <typename T> inline void LinkedList<T>::del_from_rear(size_t index) {
  throw NotImplemented();
}

template <typename T> inline size_t LinkedList<T>::length() { return length_; }

} // namespace curran
