#include <iostream>
#include "Tree.hpp"
/*
 * Test if a binary tree satisfies the BST property
 * Write a function that takes as input the root of a binary tree whose
 * nodes have a key field, and returns true if an donly if the tree satisfited the BST
 * property.
 *
 */

using std::numeric_limits;
using std::unique_ptr;

template <typename T>
bool IsBSTHelper(const unique_ptr<BinaryTreeNode<T>>& root, int lower, int upper)
{
    if (!root) {
        return true;
    } else 
    if (root->key_value < lower || root->key_value > upper) {
        return false;
    }
    return IsBSTHelper(root->left, lower, root->key_value) &&
           IsBSTHelper(root->right, root->key_value, upper);
}

template <typename T>
bool IsBST(const unique_ptr<BinaryTreeNode<T>>& root)
{
    return IsBSTHelper(root, numeric_limits<int>::min(),
            numeric_limits<int>::max());
}

int main()
{
    BinaryTree<int> *root = new BinaryTree<int>();
    const unique_ptr<BinaryTreeNode<int>>& node = unique_ptr<BinaryTreeNode<int> root>->get_root();
    root->insert(3);
    root->insert(5);
    root->insert(7);
    root->insert(11);
    //node = root->search(3); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(5); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(7); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(11); if (node) std::cout << "found " << node->key_value << std::endl;
    root->show();
    //node = root->get_root();
    //bool isbst = IsBST(node);
    //std::cout << "isbst? " << (isbst ? "yes" : "no") << std::endl;
    return 0;
}
