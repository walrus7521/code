#ifndef _Tree_h_
#define _Tree_h_

#include "pch.hpp"
#include "Heap.hpp"
#include "Fifo.hpp"
#include "List.hpp"

using namespace std;

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
void Tree_dfs(Tree<T> *root)
{
    Tree<T> *arr[32]; // = {0};
    Heap<Tree<T>*> hp = { .A = arr, .length = 1, .size = 32 };
    List<Tree<T>*> stack = { .next = nullptr, .key = nullptr, .max = &hp };
    if (root == nullptr) return;
    List_push(&stack, root);
    while (!List_empty(&stack)) {
        Tree<T> *node = List_pop(&stack);
        cout << node->key << endl;
        if (node->left) { 
            List_push(&stack, node->left);
        }
        if (node->right) {
            List_push(&stack, node->right);
        }
    }
}

template <typename T>
void Tree_bfs(Tree<T> *root)
{
    Fifo<Tree<T> *> queue = {.next = nullptr, .tail = nullptr, .key = nullptr};
    if (root == nullptr) return;
    Fifo_put(&queue, root);
    while (!Fifo_empty(&queue)) {
        Tree<T> *node = Fifo_get(&queue);
        cout << node->key << endl;
        if (node->left) { 
            Fifo_put(&queue, node->left);
        }
        if (node->right) {
            Fifo_put(&queue, node->right);
        }
    }
}

template <typename T>
void Tree_inorder(Tree<T> *root)
{
    if (root != NULL) {
        Tree_inorder(root->left);
        cout << "t: " << root->key << endl;
        Tree_inorder(root->right);
    }
}


#endif // _Tree_h_
