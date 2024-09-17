#ifndef ENGINE_COMMON_TREE_INL_
#define ENGINE_COMMON_TREE_INL_

#include "queue.h"
#include "tree.h"

template <class DataType>
void engine::BinaryTree<DataType>::Construct(std::vector<DataType> data) {
  root = new BinaryTreeNode<DataType>();
  root->data = data[0];
  engine::Queue<BinaryTreeNode<DataType>*> queue;
  queue.Push(root);

  size_t iter = 1;
  while (!queue.Empty() && iter < data.size()) {
    BinaryTreeNode<DataType>* current = queue.Front();
    queue.Pop();
    if (current != nullptr) {
      if (current->left == nullptr) {
        if (data[iter] != INT_MAX) {
          current->left = new BinaryTreeNode<DataType>();
          current->left->data = data[iter];
          queue.Push(current->left);
        }
        iter++;
      }

      if (current->right == nullptr) {
        if (data[iter] != INT_MAX) {
          current->right = new BinaryTreeNode<DataType>();
          current->right->data = data[iter];
          queue.Push(current->right);
        }
        iter++;
      }
    }
  }
}

template <class DataType>
void engine::BinaryTree<DataType>::Traverse(
    const BinaryTreeNode<DataType>* tree_node, TreeTraverseOrder order,
    std::vector<DataType>& out) const {
  if (tree_node == nullptr) {
    return;
  }

  switch (order) {
    case TreeTraverseOrder::PreOrder: {
      out.push_back(tree_node->data);
      Traverse(tree_node->left, order, out);
      Traverse(tree_node->right, order, out);
      break;
    }
    case TreeTraverseOrder::InOrder: {
      Traverse(tree_node->left, order, out);
      out.push_back(tree_node->data);
      Traverse(tree_node->right, order, out);
      break;
    }
    case TreeTraverseOrder::PostOrder: {
      Traverse(tree_node->left, order, out);
      Traverse(tree_node->right, order, out);
      out.push_back(tree_node->data);
      break;
    }
  }
}

template <class DataType>
void engine::BinaryTree<DataType>::UnitTest() {
  BinaryTree<int> int_tree;
  //int_tree.Construct({3, 5, 1, 6, 2, 0, 8, INT_MAX, INT_MAX, 7, 4});
  int_tree.Construct({0, 1, 2, 3, 4, INT_MAX, 5, INT_MAX, INT_MAX, INT_MAX, 6});
  {
    std::vector<int> traversed_tree;
    int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::PreOrder,
                      traversed_tree);
    std::cout << "{";
    for (int val : traversed_tree) {
      std::cout << val << ",";
    }
    std::cout << "}\n";
  }

  {
    std::vector<int> traversed_tree;
    int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::InOrder,
                      traversed_tree);
    std::cout << "{";
    for (int val : traversed_tree) {
      std::cout << val << ",";
    }
    std::cout << "}\n";
  }

  {
    std::vector<int> traversed_tree;
    int_tree.Traverse(int_tree.Root(), TreeTraverseOrder::PreOrder,
                      traversed_tree);
    std::cout << "{";
    for (int val : traversed_tree) {
      std::cout << val << ",";
    }
    std::cout << "}\n";
  }
}

#endif