#ifndef ENGINE_COMMON_DOUBLY_LINKED_LIST_H
#define ENGINE_COMMON_DOUBLY_LINKED_LIST_H

#include <vector>

template <class Datatype>
class DoublyLinkedList {
 public:
  struct Node {
    Datatype data = {};
    Node* prev = nullptr;
    Node* next = nullptr;
  };

  DoublyLinkedList(DoublyLinkedList&& other) noexcept;

  DoublyLinkedList(std::vector<Datatype> data);
  void Construct(std::vector<Datatype> data);
  void PushBack(Datatype data);
  DoublyLinkedList<Node>* Data() const;
  std::string ToStr() const;
  // static bool UnitTest();
 private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#include "doubly_linked_list.inl"

#endif