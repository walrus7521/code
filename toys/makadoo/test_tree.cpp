#include <iostream>
#include "Tree.hpp"

using namespace std;

int main()
{
    // Let us construct the Tree shown in the above figure
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << minDepth(root) << endl;
    return 0;
}

