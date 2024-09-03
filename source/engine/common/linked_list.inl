#ifndef ENGINE_COMMON_LINKED_LIST_INL
#define ENGINE_COMMON_LINKED_LIST_INL

#include <iostream>
#include <sstream>

#include "linked_list.h"

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
  bool success = list.Add(10);
  success |= list.Add(20);
  success |= list.Add(25, 1);

  std::cout << list[0] << list[1];

  int out_of_range_int = list[20];

  /* for (size_t i = 0; i < 100; i++) {
     list.Add(i * 5 + i);
   }*/

  std::string out = list.ToStr();
  std::cout << out.c_str();

  return true;
}
#endif
