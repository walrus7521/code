#ifndef _Tree_h_
#define _Tree_h_

#include "pch.hpp"
#include "Heap.hpp"

template <typename T>
struct Tree {
    Tree<T> *right, *left;
    T key;
};

template <typename T>
Tree<T> *Tree_create(T key)
{
    Tree<T> *r = new Tree<T>();
    r->left = r->right = nullptr;
    r->key = key;
    return r;
}

template <typename T>
void Tree_show(Tree<T> *root)
{
    if (root != NULL) {
        Tree_show(root->left);
        std::cout << "t: " << root->key << std::endl;
        Tree_show(root->right);
    }
}


#endif // _Tree_h_
