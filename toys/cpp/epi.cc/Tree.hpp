#ifndef _Tree_h_
#define _Tree_h_

#include "pch.hpp"
#include "Heap.hpp"
#include "Fifo.hpp"

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
void Tree_bfs(Tree<T> *root)
{
    Fifo<Tree<T> *> queue = {.next = nullptr, .tail = nullptr, .key = nullptr};
    Fifo_put(&queue, root);
    while (!Fifo_empty(&queue)) {
        Tree<T> *node = Fifo_get(&queue);
        std::cout << node->key << std::endl;
        std::cout << node->left << std::endl;
        std::cout << node->right << std::endl;
        if (node->left) { 
            std::cout << "putting left" << std::endl;
            Fifo_put(&queue, node->left);
        }
        if (node->right) {
            std::cout << "putting right" << std::endl;
            Fifo_put(&queue, node->right);
        }
    }
}


template <typename T>
void Tree_inorder(Tree<T> *root)
{
    if (root != NULL) {
        Tree_inorder(root->left);
        std::cout << "t: " << root->key << std::endl;
        Tree_inorder(root->right);
    }
}


#endif // _Tree_h_
