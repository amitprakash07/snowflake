#ifndef ENGINE_COMMON_TREE_INL
#define ENGINE_COMMON_TREE_INL

#include "common/util.h"
#include "queue.h"
#include "tree.h"

template <class DataType>
void engine::BinaryTree<DataType>::Construct(std::vector<DataType> data)
{
    root       = new BinaryTreeNode<DataType>();
    root->data = data[0];
    engine::Queue<BinaryTreeNode<DataType>*> queue;
    queue.Push(root);

    size_t iter = 1;
    while (!queue.Empty() && iter < data.size())
    {
        BinaryTreeNode<DataType>* current = queue.Front();
        queue.Pop();
        if (current != nullptr)
        {
            if (current->left == nullptr)
            {
                if (data[iter] != INT_MAX)
                {
                    current->left       = new BinaryTreeNode<DataType>();
                    current->left->data = data[iter];
                    queue.Push(current->left);
                }
                iter++;
            }

            if (current->right == nullptr)
            {
                if (data[iter] != INT_MAX)
                {
                    current->right       = new BinaryTreeNode<DataType>();
                    current->right->data = data[iter];
                    queue.Push(current->right);
                }
                iter++;
            }
        }
    }
}

template <class DataType>
void engine::BinaryTree<DataType>::Traverse(const BinaryTreeNode<DataType>* tree_node, TreeTraverseOrder order, std::vector<DataType>& out) const
{
    if (tree_node == nullptr)
    {
        return;
    }

    switch (order)
    {
    case TreeTraverseOrder::PreOrder:
    {
        out.push_back(tree_node->data);
        Traverse(tree_node->left, order, out);
        Traverse(tree_node->right, order, out);
        break;
    }
    case TreeTraverseOrder::InOrder:
    {
        Traverse(tree_node->left, order, out);
        out.push_back(tree_node->data);
        Traverse(tree_node->right, order, out);
        break;
    }
    case TreeTraverseOrder::PostOrder:
    {
        Traverse(tree_node->left, order, out);
        Traverse(tree_node->right, order, out);
        out.push_back(tree_node->data);
        break;
    }
    }
}

template <class DataType>
uint32_t engine::BinaryTree<DataType>::FindDepth(BinaryTreeNode<DataType>* node_to_found)
{
    std::function<uint32_t(BinaryTreeNode<DataType>*, BinaryTreeNode<DataType>*, bool)> find_depth_helper =
        [&](BinaryTreeNode<DataType>* node, BinaryTreeNode<DataType>* find, bool& is_found) -> uint32_t {
        if (node == nullptr)
        {
            return 0;
        }

        if (node == find)
        {
            is_found = true;
            return 1;
        }

        uint32_t depth = 0;
        if (!is_found)
        {
            depth = find_depth_helper(node->left, node_to_found, is_found) + 1;
        }

        if (!is_found)
        {
            depth = find_depth_helper(node->right, node_to_found, is_found) + 1;
        }

        return depth;
    };

    bool     found = false;
    uint32_t depth = find_depth_helper(root, node_to_found, found);
    return found ? depth : 0;
}

template <class DataType>
uint32_t engine::BinaryTree<DataType>::FindDepth(DataType node_to_found)
{
    std::function<uint32_t(BinaryTreeNode<DataType>*, DataType, bool&)> find_depth_helper =
        [&](BinaryTreeNode<DataType>* node, DataType find, bool& is_found) -> uint32_t {
        if (node == nullptr)
        {
            return 0;
        }

        if (node->data == find)
        {
            is_found = true;
            return 1;
        }

        uint32_t depth = 0;
        if (!is_found)
        {
            depth = find_depth_helper(node->left, find, is_found);
        }

        if (!is_found)
        {
            depth = find_depth_helper(node->right, find, is_found);
        }

        if (is_found)
        {
            depth = depth + 1;
        }

        return depth;
    };

    bool     found = false;
    uint32_t depth = find_depth_helper(root, node_to_found, found);
    return found ? depth : 0;
}

template <class DataType>
void engine::BinaryTree<DataType>::UnitTest()
{
    {
        BinaryTree<int> int_tree;
        int_tree.Construct({0, 1, 2, 3, 4, INT_MAX, 5, INT_MAX, INT_MAX, INT_MAX, 6});
        {
            std::vector<int> traversed_tree;
            int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::PreOrder, traversed_tree);
            std::cout << "{";
            for (int val : traversed_tree)
            {
                std::cout << val << ",";
            }
            std::cout << "}\n";
        }

        {
            std::vector<int> traversed_tree;
            int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::InOrder, traversed_tree);
            std::cout << "{";
            for (int val : traversed_tree)
            {
                std::cout << val << ",";
            }
            std::cout << "}\n";
        }

        {
            std::vector<int> traversed_tree;
            int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::PreOrder, traversed_tree);
            std::cout << "{";
            for (int val : traversed_tree)
            {
                std::cout << val << ",";
            }
            std::cout << "}\n";
        }
    }

    {
        BinaryTree<int> int_tree;
        int_tree.Construct({3, 5, 1, 6, 2, 0, 8, INT_MAX, INT_MAX, 7, 4});
        std::cout << "Depth of 0 is " << int_tree.FindDepth(0) << std::endl;
        std::cout << "Depth of 7 is " << int_tree.FindDepth(7) << std::endl;
        std::cout << "Depth of 6 is " << int_tree.FindDepth(4) << std::endl;
        std::cout << "Depth of 3 is " << int_tree.FindDepth(3) << std::endl;
        std::cout << "Depth of 200 is " << int_tree.FindDepth(200) << std::endl;
    }
}

template <class DataType>
void engine::BinarySearchTree<DataType>::Construct(std::vector<DataType> data)
{
    for (DataType datum : data)
    {
        Add(datum);
    }
}

template <class DataType>
void engine::BinarySearchTree<DataType>::Add(DataType data)
{
    if (BinaryTree<DataType>::root == nullptr)
    {
        BinaryTree<DataType>::root       = new BinaryTreeNode<DataType>();
        BinaryTree<DataType>::root->data = data;
    }
    else
    {
        Add(BinaryTree<DataType>::root, data);
    }
}

template <class DataType>
DoublyLinkedList<DataType> engine::BinarySearchTree<DataType>::Convert()
{
    std::vector<DataType> out;
    BinaryTree<DataType>::Traverse(BinaryTree<DataType>::root, TreeTraverseOrder::InOrder, out);
    return std::move(DoublyLinkedList<DataType>(out));
}

template <class DataType>
void engine::BinarySearchTree<DataType>::UnitTest()
{
    BinarySearchTree<int> int_bst;
    int_bst.Construct({10, 5, 15, 3, 8, 11, 7});
    std::vector<int> tree_traverse;
    int_bst.Traverse(int_bst.Root(), TreeTraverseOrder::InOrder, tree_traverse);
    std::cout << engine::util::ToStr(tree_traverse);
    DoublyLinkedList<int> int_dll = int_bst.Convert();
    std::cout << int_dll.ToStr();
}

template <class DataType>
void engine::BinarySearchTree<DataType>::Add(BinaryTreeNode<DataType>* node, DataType data)
{
    BinaryTreeNode<DataType>* next  = node;
    bool                      added = false;
    while (!added)
    {
        if (next)
        {
            if (data >= next->data)
            {
                if (next->right == nullptr)
                {
                    next->right       = new BinaryTreeNode<DataType>();
                    next->right->data = data;
                    added             = true;
                }
                else
                {
                    next = next->right;
                }
            }
            else
            {
                if (next->left == nullptr)
                {
                    next->left       = new BinaryTreeNode<DataType>();
                    next->left->data = data;
                    added            = true;
                }
                else
                {
                    next = next->left;
                }
            }
        }
    }
}

#endif
