#ifndef H_VEC
#include <cstring>
#include <optional>

#include "common.h"

#define INITIAL_LEN 8
#define GROWTH_RATE 2

namespace curran {

template <typename T> class Vector {
public:
  Vector();
  Vector(size_t capacity);
  Vector(size_t length, T val);
  ~Vector();
  T &operator[](size_t index);
  void push(T val);
  std::optional<T> pop();
  void clear();

private:
  void grow_capacity();
  size_t length;
  size_t capacity;
  T *array;
};

template <typename T> inline Vector<T>::Vector() {
  length = 0;
  capacity = INITIAL_LEN;
  this->array = new T[INITIAL_LEN];
}

template <typename T> inline Vector<T>::Vector(size_t capacity) {
  length = 0;
  this->capacity = capacity;
  this->array = new T[capacity];
}

template <typename T>
inline Vector<T>::Vector(size_t length, T val) : Vector(length) {
  for (auto i = 0; i < length; i++) {
    this->array[i] = val;
  }
}

template <typename T> inline Vector<T>::~Vector() { delete[] this->array; }

template <typename T> inline T &Vector<T>::operator[](size_t index) {
  if (index >= length) {
      throw IndexError("Attempted access outside of bounds");
  }
  return this->array[index];
}

template <typename T> inline void Vector<T>::push(T val) {
  if (length >= capacity) {
    this->grow_capacity();
  }
  this->array[length] = val;
  length++;
}

template <typename T> inline void Vector<T>::grow_capacity() {
  size_t next_capacity = this->capacity * GROWTH_RATE;
  T *next_array = new T[next_capacity];
  std::memcpy(next_array, this->array, this->capacity * sizeof(T));
  this->capacity = next_capacity;
  delete[] this->array;
  this->array = next_array;
}

template <typename T> inline std::optional<T> Vector<T>::pop() {
  std::optional<T> val;
  if (this->length == 0) {
    return val;
  } else {
    val = this->array[length - 1];
    this->length--;
    return val;
  }
}

template <typename T> inline void Vector<T>::clear() { this->length = 0; }

} // namespace curran
#endif // H_VEC
