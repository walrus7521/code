#include <iostream>
#include <utility>
#include <algorithm>
#include "Tree.hpp"

using std::pair;
using std::max;

/* the first value of the return value indicates if tree is balanced, and if
 * balanced the second value is the height of the tree.
 */
template <typename T>
pair<bool, int> CheckBalanced(BinaryTreeNode<T> *tree) {
    if (tree == nullptr) {
        return {true, -1}; // base case
    }

    auto left_result = CheckBalanced(tree->left);
    if (!left_result.first) {
        return {false, 0}; // left subtree is not balanced
    }

    auto right_result = CheckBalanced(tree->right);
    if (!right_result.first) {
        return {false, 0}; // right subtree is not balanced
    }

    bool is_balanced = abs(left_result.second - right_result.second) <= 1;
    int height = max(left_result.second, right_result.second) + 1;
    return {is_balanced, height};
}

bool IsBalanceBinaryTree(BinaryTreeNode<int> *tree) {
    return CheckBalanced(tree).first;
}

int main()
{
    BinaryTree<int> *root = new BinaryTree<int>();
    BinaryTreeNode<int> *node;
    //root->insert(3); root->insert(5); root->insert(7); root->insert(11);
    root->insert(4); root->insert(2); root->insert(8); root->insert(1); root->insert(5);
    //node = root->search(3); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(5); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(7); if (node) std::cout << "found " << node->key_value << std::endl;
    //node = root->search(11); if (node) std::cout << "found " << node->key_value << std::endl;
    root->show();
    node = root->get_root();
    bool isbal = IsBalanceBinaryTree(node);
    std::cout << "Is balanced? " << (isbal ? "yes" : "no") << std::endl;
    return 0;
}
