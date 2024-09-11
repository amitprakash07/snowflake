#ifndef ENGINE_COMMON_LINKED_LIST_INL
#define ENGINE_COMMON_LINKED_LIST_INL

#include <iostream>
#include <sstream>

//#include "linked_list.h"

template <typename DataType>
engine::LinkedList<DataType>::LinkedList() {
  head_ = new Node();
  count_ = 0;
}

template <typename DataType>
engine::LinkedList<DataType>::LinkedList(DataType data) : LinkedList() {
  Node* new_node = new Node();
  new_node->data = data;

  head_->next = new_node;
  count_ = 1;
}
template <typename DataType>
engine::LinkedList<DataType>::~LinkedList<DataType>() {
  while (head_) {
    Node* next_node = head_->next;
    delete head_;
    head_ = next_node;
  }

  count_ = 0;
  head_ = nullptr;
}

template <typename DataType>
bool engine::LinkedList<DataType>::Add(DataType data, int index) {
  if (index != -1 && static_cast<size_t>(index) > count_) {
    throw std::out_of_range("Index out of range");
    return false;
  }

  Node* new_node = new Node();
  new_node->data = data;

  // index == 0 i.e. at head
  if (index == 0 || ((index == -1) && head_->next == nullptr)) {
    new_node->next = head_->next;
    head_->next = new_node;
  } else {
    size_t list_index_iter = 0;
    Node* list_iter = head_->next;

    while (list_iter && list_iter->next != nullptr) {
      if (list_index_iter == static_cast<size_t>(index) - 1) {
        new_node->next = list_iter->next;
        list_iter->next = new_node;
        break;
      }
      list_iter = list_iter->next;
      list_index_iter++;
    }

    if (index == -1 || (static_cast<size_t>(index) - 1) == count_) {
      list_iter->next = new_node;
    }
  }

  count_++;
  return true;
}
template <typename DataType>
size_t engine::LinkedList<DataType>::Size() const {
  return count_;
}

template <typename DataType>
DataType engine::LinkedList<DataType>::Remove(int index) {
  return DataType();
}

template <typename DataType>
DataType engine::LinkedList<DataType>::operator[](size_t index) const {
  if (index > count_) {
    throw std::out_of_range("Index out of range");
  } else {
    Node* list_iter = head_->next;
    size_t list_index_iter = 0;

    while (list_iter) {
      if (list_index_iter == index) {
        break;
      }
      list_iter = list_iter->next;
      list_index_iter++;
    }

    return list_iter->data;
  }
}
template <typename DataType>
DataType engine::LinkedList<DataType>::GetMiddle() const {
  if (head_ && head_->next) {
    Node* dummy = head_->next;  // start of link list

    Node* slow_ptr = dummy;
    Node* fast_ptr = dummy;

    while (fast_ptr && fast_ptr->next) {
      slow_ptr = slow_ptr->next;
      fast_ptr = fast_ptr->next->next;
    }

    return slow_ptr->data;
  }

  return DataType();
}
template <typename DataType>
void engine::LinkedList<DataType>::Reverse() {
  if (head_ && head_->next) {
    Node* prev = nullptr;
    Node* current = head_->next;

    while (current) {
      Node* next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    head_->next = prev;
  }
}

template <typename DataType>
std::string engine::LinkedList<DataType>::ToStr() const {
  std::stringstream ss;
  Node* iter = head_->next;
  ss << "{";
  while (iter) {
    ss << iter->data << "->";
    iter = iter->next;
  }

  const std::string temp(ss.str());
  std::string ret_str(temp.cbegin(), temp.cend() - 2);
  ret_str += '}';
  return ret_str;
}

template <typename DataType>
bool engine::LinkedList<DataType>::UnitTest() {
  LinkedList<int> list;

  bool success = true;
  for (int i = 1; i < 7; i++) {
    success |= list.Add(i);
  }

  std::string out = list.ToStr();
  std::cout << out.c_str();

  std::cout << list.GetMiddle() << endl;

  list.Reverse();
  std::cout << list.ToStr();

  std::cout << list.GetMiddle() << endl;

  return true;
}
#endif
