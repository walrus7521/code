#include <iostream>

template <typename T>
class BinaryTreeNode {
public:
    BinaryTreeNode<T>() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    };
    ~BinaryTreeNode<T>() {
        delete left;
        delete right;
        delete parent;
    }
//private:
    T key_value, max, min;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    BinaryTreeNode<T> *parent;
};

template <typename T>
class BinaryTree {
public:
    BinaryTree<T>() { root = nullptr; }
    ~BinaryTree<T>() { destroy_tree(); }
    void destroy_tree() { destroy_tree(root); }
    void destroy_tree(BinaryTreeNode<T> *tree) { 
        if (tree != nullptr) {
            destroy_tree(tree->left);
            destroy_tree(tree->right);
            delete tree;
        }
    }
    void insert(T key) {
        if(root != nullptr) {
            insert(key, root);
        } else {
            root = new BinaryTreeNode<T>();
            root->key_value = key;
            root->left = nullptr;
            root->right = nullptr;
        }        
    }
    BinaryTreeNode<T> *search(T key) {
        return search(root, key);
    }

    void show() {
        show(root);
    }
    BinaryTreeNode<T> *get_root() {
        return this->root;
    }
private:
    BinaryTreeNode<T> *search(BinaryTreeNode<T> *tree, T key) {
        if(tree != nullptr) {
            if(key==tree->key_value)
                return tree;
            if(key<tree->key_value)
                return search(tree->left, key);
            else
                return search(tree->right, key);
        }
        else return nullptr;

    }
    void insert(T key, BinaryTreeNode<T> *leaf) {
        if(key < leaf->key_value) {
            if(leaf->left != nullptr) {
                insert(key, leaf->left);
            } else {
                leaf->left = new BinaryTreeNode<T>();
                leaf->left->key_value = key;
                leaf->left->left = nullptr;    //Sets the left child of the child node to null
                leaf->left->right = nullptr;   //Sets the right child of the child node to null
            }  
        } else 
        if(key >= leaf->key_value) {
            if(leaf->right != nullptr) {
                insert(key, leaf->right);
            } else {
                leaf->right = new BinaryTreeNode<T>();
                leaf->right->key_value = key;
                leaf->right->left = nullptr;  //Sets the left child of the child node to null
                leaf->right->right = nullptr; //Sets the right child of the child node to null
            }
        }    
    }
    void show(BinaryTreeNode<T> *tree) {
        if (tree != nullptr) {
            show(tree->left);
            std::cout << tree->key_value << std::endl;
            show(tree->right);
        }
    }

    BinaryTreeNode<T> *root;
};


#include <iostream>
#include <utility>
#include <algorithm>

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

