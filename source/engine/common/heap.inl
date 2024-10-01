#ifndef ENGINE_COMMON_HEAP_INL
#define ENGINE_COMMON_HEAP_INL

#include <iostream>
#include <stdexcept>

#include "heap.h"
#include "util.h"

namespace engine {

template <typename DataType, HeapType type, size_t init_size>
Heap<DataType, type, init_size>::Heap(std::vector<DataType> init_data)
    : Heap() {
  if (init_data.size() > buffer_size_) {
    buffer_size_ = init_data.size();
    data_.resize(buffer_size_);
  }

  for (DataType data : init_data) {
    Push(data);
  }
}

template <typename DataType, HeapType type, size_t init_size>
void Heap<DataType, type, init_size>::Push(DataType data) {
  if (buffer_size_ < current_size_ + 1) {
    data_.resize(buffer_size_ * 2);
  }

  data_[current_size_] = data;
  size_t add_index = current_size_;
  size_t parent_index = Parent(add_index);
  while (data_[parent_index] < data_[add_index]) {
    DataType temp = data_[add_index];
    data_[add_index] = data_[parent_index];
    data_[parent_index] = temp;
    add_index = parent_index;
    parent_index = Parent(add_index);
  }
  current_size_++;
}

template <typename DataType, HeapType type, size_t init_size>
void Heap<DataType, type, init_size>::Pop()
{
    
}

template <typename DataType, HeapType type, size_t init_size>
DataType Heap<DataType, type, init_size>::Top() const {
  if (!Empty()) {
    return data_[0];
  }

  throw std::out_of_range("Empty heap");
}

template <typename DataType, HeapType type, size_t init_size>
std::string Heap<DataType, type, init_size>::ToStr() const {
  return util::ToStr(data_);
}

template <typename DataType, HeapType type, size_t init_size>
void Heap<DataType, type, init_size>::UnitTest() {
  Heap<int> int_heap({3, 2, 4, 1, 5, 9});
  std::cout << int_heap.ToStr().c_str();
}
}  // namespace engine

#endif
