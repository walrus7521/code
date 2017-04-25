#include <stdio.h>
#include "tree.h"

int main()
{
    // Let us construct the Tree shown in the above figure
    Node *root        = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    printf("min depth: %d\n", minDepth(root));
    return 0;
}

