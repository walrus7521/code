#include "pch.hpp"
#include "Tree.hpp"

using namespace std;

void test_tree()
{
    Tree<int> root = { .left = nullptr, .right = nullptr, .key = 42 };
    root.left        = Tree_create(2);
    root.right       = Tree_create(3);
    root.left->left  = Tree_create(4);
    root.left->right = Tree_create(5);
    cout << "bfs: " << endl;
    Tree_bfs(&root);
    cout << "dfs: " << endl;
    Tree_dfs(&root);
}

int main()
{
    test_tree();
}

