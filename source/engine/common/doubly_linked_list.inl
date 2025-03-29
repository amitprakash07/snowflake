#include "doubly_linked_list.h"

template <class Datatype>
DoublyLinkedList<Datatype>::DoublyLinkedList(std::vector<Datatype> data)
{
    for (Datatype datum : data)
    {
        PushBack(datum);
    }
}

template <class Datatype>
DoublyLinkedList<Datatype>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
{
    head_       = other.head_;
    tail_       = other.tail_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <class Datatype>
void DoublyLinkedList<Datatype>::Construct(std::vector<Datatype> data)
{
    for (Datatype datum : data)
    {
        PushBack(datum);
    }
}

template <class Datatype>
void DoublyLinkedList<Datatype>::PushBack(Datatype data)
{
    if (head_ == nullptr)
    {
        head_       = new Node();
        tail_       = head_;
        head_->data = data;
    }
    else
    {
        Node* new_node = new Node();
        new_node->data = data;
        new_node->prev = tail_;
        tail_->next    = new_node;
        tail_          = new_node;
    }
}

template <class Datatype>
DoublyLinkedList<typename DoublyLinkedList<Datatype>::Node>* DoublyLinkedList<Datatype>::Data() const
{
    return head_;
}

template <class Datatype>
std::string DoublyLinkedList<Datatype>::ToStr() const
{
    std::stringstream ss;
    Node*             iter = head_;
    ss << "{";
    while (iter)
    {
        ss << iter->data << "->";
        iter = iter->next;
    }

    const std::string temp(ss.str());
    std::string       ret_str(temp.cbegin(), temp.cend() - 2);
    ret_str += '}';
    return ret_str;
}
