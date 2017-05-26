#include <iostream>

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
void Tree_inorder(Tree<T> *root)
{
    if (root != NULL) {
        Tree_inorder(root->left);
        cout << "t: " << root->key << endl;
        Tree_inorder(root->right);
    }
}

int main()
{
    //Tree<int> root = { .left = nullptr, .right = nullptr, .key = 42 };
    Tree<int> root;
    root.key = 42;

    root.left        = Tree_create(2);
    root.right       = Tree_create(3);
    root.left->left  = Tree_create(4);
    root.left->right = Tree_create(5);
    Tree_inorder(&root);
}


