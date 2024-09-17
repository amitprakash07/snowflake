#ifndef ENGINE_COMMON_STACK_H
#define ENGINE_COMMON_STACK_H

#include <string>

namespace engine {
    template<class DataType, uint32_t initial_size = 100>
    class Stack
    {
    public:
        Stack();
        void Push(DataType data);
        void Pop();
        DataType Top();
        uint32_t Size() const;
        bool Empty() const;
        std::string Print() const;
        static void UnitTest();
    private:
        void ResizeAndMove(uint32_t new_size);
        DataType* storage_;
        uint32_t max_container_element_count_;
        uint32_t top_index_;
        bool empty_;
    };
}  // namespace engine

#include "stack.inl"

#endif
