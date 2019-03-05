/*  C/C++ program to flip a binary tree */
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std; 
  
struct Node { 
    int data; 
    Node *left, *right; 
}; 
  
struct Node* newNode(int data) 
{ 
    struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
    temp->data = data; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
Node* flip_tree(Node* root) 
{ 
    // Base cases 
    if (root == NULL) return root; 
    if (root->left == NULL && root->right == NULL) return root; 
  
    //  recursively call the same method 
    Node* flippedRoot = flip_tree(root->left); 
  
    //  rearranging main root Node after returning from recursive call 
    root->left->left = root->right; 
    root->left->right = root; 
    root->left = root->right = NULL; 
  
    return flippedRoot; 
} 
  
void level_traverse(Node *root) 
{ 
    if (root == NULL)  return; 
  
    queue<Node *> q; 
    q.push(root); 
  
    int node_count;
    while ((node_count = q.size())) { 
        // Dequeue all nodes of current level and Enqueue all nodes of next level 
        while (node_count > 0) { 
            Node *node = q.front(); 
            printf("%d ", node->data);
            q.pop(); 
            if (node->left != NULL) q.push(node->left); 
            if (node->right != NULL) q.push(node->right); 
            node_count--; 
        } 
        printf("\n");
    } 
} 

int main() 
{ 
    // manually build a tree
    Node* root = newNode(1); 
    root->left = newNode(2); 
    root->right = newNode(3); 
    root->right->left = newNode(4); 
    root->right->right = newNode(5); 
  
    printf("Level order traversal of given tree\n");
    level_traverse(root); 
  
    root = flip_tree(root); 
  
    printf("\nLevel order traversal of the flipped tree\n");
    level_traverse(root); 
    return 0; 
} 

