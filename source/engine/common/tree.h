#ifndef ENGINE_COMMON_TREE_H
#define ENGINE_COMMON_TREE_H

#include <cstdint>
#include <vector>
#include <string>

enum class TreeTraverseOrder
{
    PreOrder,
    InOrder,
    PostOrder
};

template<class DataType, uint8_t Dimension, bool ArrayStorage>
class TreeNode
{
public:
    TreeNode() : data() {}
    DataType data;
protected:
    uint8_t dimension = Dimension;
    bool use_array_storage = ArrayStorage;
};

template<class DataType>
class BinaryTreeNode : public TreeNode<DataType, 2, false>
{
public:
    TreeNode<DataType, 2, false>* left = nullptr;
    TreeNode<DataType, 2, false>* right = nullptr;
};

template<class DataType>
class BinaryTree
{
public:
    void Construct(std::vector<DataType> data);
    std::string Traverse(BinaryTreeNode<DataType>* tree_node, TreeTraverseOrder order);
    static void UnitTest();
private:
    BinaryTreeNode<DataType>* root = nullptr;
};

template<class DataType>
class BinarySearchTree : public BinaryTree<DataType>
{
public:
};

#endif
