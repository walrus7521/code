#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct Tree {
    shared_ptr<Tree<T>> right, left;
    T key;
};

template <typename T>
shared_ptr<Tree<T>> Tree_create(T key)
{
    shared_ptr<Tree<T>> r(new Tree<T>);
    r->left = r->right = nullptr;
    r->key = key;
    return r;
}

template <typename T>
void Tree_inorder(shared_ptr<Tree<T>> root)
{
    if (root != NULL) {
        Tree_inorder(root->left);
        cout << "t: " << root->key << endl;
        Tree_inorder(root->right);
    }
}

int main()
{
    shared_ptr<Tree<int>> root = Tree_create<int>(42);
    
    root->left        = Tree_create(2);
    root->right       = Tree_create(3);
    root->left->left  = Tree_create(4);
    root->left->right = Tree_create(5);
    Tree_inorder(root);
}

