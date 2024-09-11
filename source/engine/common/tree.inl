#include "tree.h"

template <class DataType>
void BinaryTree<DataType>::Construct(std::vector<DataType> data) {
    root = new BinaryTreeNode<DataType>();
    root->data = data[0];
    if (!data.empty()) 
  {

    for (int val : data)
    {
      if (val == INT_MAX)
      {
          
      }
    }
  }
}

template <class DataType>
void BinaryTree<DataType>::UnitTest() {
  BinaryTree<int> int_tree;
  int_tree.Construct({3, 5, 1, 6, 2, 0, 8, INT_MAX, INT_MAX, 7, 4});
}