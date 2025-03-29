#ifndef ENGINE_COMMON_TREE_H
#define ENGINE_COMMON_TREE_H

#include <cstdint>
#include <string>
#include <vector>

#include "doubly_linked_list.h"

namespace engine
{

    enum class TreeTraverseOrder
    {
        PreOrder,
        InOrder,
        PostOrder
    };

    template <class DataType, uint8_t Dimension, bool ArrayStorage>
    class TreeNode
    {
    public:
        TreeNode()
            : data()
        {
        }
        DataType data;

    protected:
        uint8_t dimension         = Dimension;
        bool    use_array_storage = ArrayStorage;
    };

    template <class DataType>
    class BinaryTreeNode : public TreeNode<DataType, 2, false>
    {
    public:
        BinaryTreeNode* left  = nullptr;
        BinaryTreeNode* right = nullptr;
    };

    template <class DataType>
    class BinaryTree
    {
    public:
        void                            Construct(std::vector<DataType> data);
        void                            Traverse(const BinaryTreeNode<DataType>* tree_node, TreeTraverseOrder order, std::vector<DataType>& out) const;
        const BinaryTreeNode<DataType>* Root() const
        {
            return root;
        }
        uint32_t    FindDepth(BinaryTreeNode<DataType>* node_to_found);
        uint32_t    FindDepth(DataType node_to_found);
        static void UnitTest();

    protected:
        BinaryTreeNode<DataType>* root = nullptr;
    };

    template <class DataType>
    class BinarySearchTree : public BinaryTree<DataType>
    {
    public:
        void                       Construct(std::vector<DataType> data);
        void                       Add(DataType data);
        DoublyLinkedList<DataType> Convert();

        static void UnitTest();

    private:
        void Add(BinaryTreeNode<DataType>* node, DataType data);
    };

}  // namespace engine
#include "tree.inl"

#endif
