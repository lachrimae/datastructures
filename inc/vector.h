#pragma once
#include <bit>
#include <cstring>
#include <optional>
#include <stdexcept>
#include <utility>

constexpr size_t vector_initial_len__ = 8;
constexpr size_t vector_growth_rate__ = 2;

namespace curran {

template <typename T> class Vector {
public:
  Vector();
  Vector(size_t capacity);
  Vector(size_t length_, T val);
  Vector(const Vector &);
  ~Vector();
  T &operator[](size_t index);
  const T &operator[](size_t index) const;
  void push(T val);
  std::optional<T> pop();
  void clear();
  size_t length() const;

private:
  void grow_capacity();
  size_t length_;
  size_t capacity;
  T *array;
};

template <typename T> inline Vector<T>::Vector() {
  length_ = 0;
  capacity = vector_initial_len__;
  array = new T[vector_initial_len__];
}

template <typename T> inline Vector<T>::Vector(size_t cap) {
  length_ = 0;
  capacity = cap;
  array = new T[cap];
}

template <typename T> inline Vector<T>::~Vector() { delete[] array; }

template <typename T>
inline Vector<T>::Vector(size_t length_, T val) : Vector(length_) {
  for (auto i = 0; i < length_; i++) {
    array[i] = val;
  }
}

template <typename T> inline Vector<T>::Vector(const Vector<T> &other) {
  length_ = other.length_;
  capacity = std::bit_ceil<size_t>(length_);
  array = new T[capacity];
  std::memcpy(array, other.array, length_ * sizeof(T));
}

template <typename T> inline T &Vector<T>::operator[](size_t index) {
  return const_cast<T &>(std::as_const(*this)[index]);
}

template <typename T>
inline const T &Vector<T>::operator[](size_t index) const {
  if (index >= length_) {
    throw std::out_of_range("Index out of range");
  }
  return array[index];
}

template <typename T> inline void Vector<T>::push(T val) {
  if (length_ >= capacity) {
    grow_capacity();
  }
  array[length_] = val;
  length_++;
}

template <typename T> inline void Vector<T>::grow_capacity() {
  T *old_array = array;
  size_t old_capacity = capacity;
  capacity *= vector_growth_rate__;
  array = new T[capacity];
  std::memcpy(array, old_array, old_capacity * sizeof(T));
  delete[] old_array;
}

template <typename T> inline std::optional<T> Vector<T>::pop() {
  std::optional<T> val;
  if (length_ == 0) {
    return val;
  } else {
    val = array[length_ - 1];
    length_--;
    return val;
  }
}

template <typename T> inline void Vector<T>::clear() { length_ = 0; }

template <typename T> inline size_t Vector<T>::length() const {
  return length_;
}

} // namespace curran
