#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void tree_inorder(tree_t *root)
{
    if (root) {
        tree_inorder(root->left);
        printf("%d\n", root->key);
        tree_inorder(root->right);
    }
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

tree_t *tree_insert(tree_t *root, tree_t *newnode)
{
    if (!root) {
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
    int a[] = {1,2,3,4,5};
    int len = sizeof(a) / sizeof(a[0]);
    int i;
    tree_t *root = NULL;
    for (i = 0; i < len; i++) {
        tree_t *newnode = tree_create(a[i]);
        root = tree_insert(root, newnode);
    }
    tree_inorder(root);
    for (i = 0; i < len; i++) {
        tree_t *find = tree_search(root, a[i]);
        if (find) {
            printf("found %d\n", find->key);
        } else {
            printf("%d not found\n", a[i]);
        }
    }
}




