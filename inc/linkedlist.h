#ifndef H_LINKED_LIST
#define H_LINKED_LIST

#include <optional>
#include <stdexcept>

#include "common.h"
#include "vector.h"

namespace curran {

template <typename T>
struct Node {
    T val;
    Node<T> *prev;
    Node<T> *next;
}

template <typename T>
class LinkedList {
private:
    Node<T> *initial;
    Node<T> *terminal;
    size_t length;
    void insert_from_rear(size_t index, T val);
    void insert_from_front(size_t index, T val);
    void del_from_front(size_t index, T val);
    void del_from_rear(size_t index, T val);
public:
    LinkedList();
    LinkedList(Vector<T> vec);
    ~LinkedList();
    void push(T val);
    std::optional<T> pop();
    void push_front(T val);
    std::optional<T> pop_front();
    void insert(size_t index, T val);
    void del(size_t index);
};

template <typename T>
inline LinkedList::LinkedList() {
    this->initial = NULL;
    this->terminal = NULL;
    this->length = 0;
}

template <typename T>
inline LinkedList::LinkedList(Vector<T> vec) : LinkedList() {
    while (true) {
        std::optional<T> val = vec.pop();
        if (!val.has_value()) {
            break;
        }
        this->push_front(val.value());
    }
}

template <typename T>
inline LinkedList::~LinkedList() {
    Node<T> *current = this->initial;
    while (current) {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
inline void LinkedList::push(T val) {
    Node<T> *node = new Node;
    node->prev = this->terminal;
    node->next = NULL;
    node->val = val;
    if (this->terminal) {
      this->terminal->next = node;
    } else {
      this->initial = node;
    }
    this->terminal = node;
    this->length++;
}

template <typename T>
inline std::optional<T> LinkedList::pop() {
    if (this->length <= 0) {
        return std::optional();
    }
    Node<T> *terminal = this->terminal;
    T val = terminal->val;
    if (this->initial == terminal) {
        this->initial = NULL;
    }
    this->terminal = terminal->prev;
    this->length--;
    delete terminal;
    return std::optional(val);
}

template <typename T>
inline void LinkedList push_front(T val) {
    Node<T> *node = new Node;
    node->prev = NULL;
    node->next = this->initial;
    node->val = val;
    if (this->initial) {
        this->initial->prev = node;
    } else {
        this->terminal = node;
    }
    this->initial = node;
    this->length++;
}

template <typename T>
inline std::optional<T> LinkedList::pop_front() {
    if (this->length <= 0) {
        return std::optional();
    }
    Node<T> *initial = this->initial;
    T val = initial->val;
    if (this->terminal == initial) {
        this->terminal = NULL;
    }
    this->initial = initial->next;
    this->length--;
    delete initial;
    return std::optional(val);
}

template <typename T>
inline void LinkedList::insert(size_t index, T val) {
    if (index == 0) {
        this->push_front(val);
        return;
    } else if (index == this->length) {
        this->push(val);
        return;
    } else if (index > this->length || index < 0) {
        throw IndexError();
    }
    if (index * 2 > this->length) {
        this->insert_from_rear(index, val);
    } else {
        this->insert_from_front(index, val);
    }
}

template <typename T>
inline void LinkedList::insert_from_front(size_t index, T val) {
    return;
}

template <typename T>
inline void LinkedList::insert_from_rear(size_t index, T val) {
    return;
}

} // namespace curran

#endif // H_LINKED_LIST
