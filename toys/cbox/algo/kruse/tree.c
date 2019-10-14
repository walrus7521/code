#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int nodes = 0;
void tree_inorder(tree_t *root)
{
    if (root) {
        tree_inorder(root->left);
        printf("%d\n", root->key);
        tree_inorder(root->right);
    }
}

void tree_postorder(tree_t *root)
{
    if (root) {
        tree_postorder(root->left);
        tree_postorder(root->right);
        printf("%d\n", root->key);
    }
}

void postOrderIterative(tree_t *root) 
{ 
    tree_t *stack[32];
    int head = 0;
 
    // Check for empty tree 
    if (root == NULL) 
        return;
    do
    { 
        // Move to leftmost node 
        while (root) 
        { 
            // Push root's right child and then root to stack. 
            if (root->right) 
                stack[head++] = root->right; 
            stack[head++] = root; 
  
            // Set root as root's left child   
            root = root->left; 
        } 
  
        // Pop an item from stack and set it as root     
        root = stack[--head]; 
  
        // If the popped item has a right child and the right child is not 
        // processed yet, then make sure right child is processed before root 
        if (root->right && stack[head] == root->right) 
        { 
            --head;  // remove right child from stack 
            stack[head++] = root; // push root back to stack 
            root = root->right; // change root so that the right  
                                // child is processed next 
        } 
        else  // Else print root's data and set root as NULL 
        { 
            printf("%d ", root->key); 
            root = NULL; 
        } 
    } while (head >= 0); 
    printf("\n");
} 

tree_t *tree_search(tree_t *root, key_t target)
{
    if (root) {
        if (target < root->key) {
            root = tree_search(root->left, target);
        }
        else if (target > root->key) {
            root = tree_search(root->right, target);
        }
    }
    return root;
}

#define MAX_DEPTH 16
int _print_t(tree_t *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
    //sprintf(b, "(%c)", tree->key);
    left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    } else if (depth && !is_left) {
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    }
    return left + width + right;
}

int print_t(tree_t *tree)
{
    char s[MAX_DEPTH][255];
    int i;
    for (i = 0; i < MAX_DEPTH; i++)
        sprintf(s[i], "%80s", " ");
    _print_t(tree, 0, 0, 0, s);
    for (i = 0; i < MAX_DEPTH; i++)
        printf("%s\n", s[i]);
    return 0;
}


void bfs(tree_t *root)
{
    tree_t *queue[16];
    int head=0, tail=0;
    queue[tail++] = root;
    root->level = 0;
    while (head != tail) {
        tree_t *t = queue[head++];
        printf("%02d %02d\n", t->key, t->level);
        if (t->left) {
            queue[tail++] = t->left;
            t->left->level = t->level+1;
        }
        if (t->right) {
            queue[tail++] = t->right;
            t->right->level = t->level+1;
        }
    }
}

void dfs(tree_t *root)
{
    tree_t *stack[16];
    int head=0;
    root->level = 0;
    tree_t *t = root;
    nodes--;
    stack[head++] = root;
    while (nodes > 0) {
        if (t->left) {
            stack[head++] = t->left;
            t->left->level = t->level+1;
            nodes--;
        }
        if (t->right) {
            stack[head++] = t->right;
            t->right->level = t->level+1;
            nodes--;
        }
    }
    while (head >= 0) {
        tree_t *t = stack[--head];
        printf("%02d\n", t->key);

    }
}

tree_t *tree_insert(tree_t *root, tree_t *newnode)
{
    if (!root) {
        nodes++;
        root = newnode;
        root->left = root->right = NULL;
    } else
    if (newnode->key < root->key) {
        root->left = tree_insert(root->left, newnode);
    } else {
        root->right = tree_insert(root->right, newnode);
    }
    return root;
}

tree_t *tree_create(key_t key)
{
    tree_t *newnode = (tree_t *) malloc(sizeof(tree_t));
    newnode->key = key;
    newnode->left = newnode->right = NULL;
    return newnode;
}

int main()
{
    //int a[] = {3,4,5,2,1};
    int a[] = {10, 5, 4, 3, 7, 16, 13, 11, 20, 18, 17, 19, 30};
    int len = sizeof(a) / sizeof(a[0]);
    int i;
    tree_t *root = NULL;
    for (i = 0; i < len; i++) {
        tree_t *newnode = tree_create(a[i]);
        root = tree_insert(root, newnode);
    }
    printf("num nodes: %d\n", nodes);
    //tree_inorder(root);
    //tree_postorder(root);
    postOrderIterative(root); 
    //bfs(root);
    //dfs(root);
    print_t(root);
    for (i = 0; i < len; i++) {
        tree_t *find = tree_search(root, a[i]);
        if (find) {
            printf("found %d\n", find->key);
        } else {
            printf("%d not found\n", a[i]);
        }
    }
}




