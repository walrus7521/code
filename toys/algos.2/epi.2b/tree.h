#include <stdlib.h>

int min(int a, int b)
{
    return (a < b) ? a : b;
}

// A BT Node
typedef struct _Node
{
    int data;
    struct _Node* left, *right;
} Node;
 
int minDepth(Node *root)
{
    // Corner case. Should never be hit unless the code is 
    // called on root = NULL
    if (root == NULL)
        return 0;
 
    // Base case : Leaf Node. This accounts for height = 1.
    if (root->left == NULL && root->right == NULL)
       return 1;
 
    // If left subtree is NULL, recur for right subtree
    if (!root->left)
       return minDepth(root->right) + 1;
 
    // If right subtree is NULL, recur for right subtree
    if (!root->right)
       return minDepth(root->left) + 1;
 
    return min(minDepth(root->left), minDepth(root->right)) + 1;
}
 
// Utility function to create new Node
Node *newNode(int data)
{
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->data  = data;
    temp->left  = temp->right = NULL;
    return (temp);
}
 
