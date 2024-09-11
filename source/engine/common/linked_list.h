#ifndef ENGINE_COMMON_LINKED_LIST_H
#define ENGINE_COMMON_LINKED_LIST_H

namespace engine {
template <typename DataType>
class LinkedList {
 public:
  LinkedList();
  LinkedList(DataType data);

    ~LinkedList();

  [[nodiscard]] bool Add(DataType data, int index = -1);
  size_t Size() const;
  DataType Remove(int index = -1);
  DataType operator[](size_t index) const;
  DataType GetMiddle() const;
  void Reverse();

  std::string ToStr() const;

  static bool UnitTest();

 private:
  struct Node {
    Node() : data(), next(nullptr) {}
    DataType data;
    Node* next = nullptr;
  };

  // sentinel pointers
  Node* head_ = nullptr;
  size_t count_ = 0;
};

}  // namespace engine

#include "linked_list.inl"

#endif
