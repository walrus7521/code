#include "types.h"

void show(tree_t *tree)
{
    if (tree->left) show(tree->left);
    printf("key: %d\n", tree->key);
    if (tree->right) show(tree->right);
}

int height(tree_t *tree)
{
    return 0;
}

tree_t *new(int key)
{
    tree_t *t = malloc(sizeof(tree_t));
    t->left = t->right = NULL;
    t->key = key;
    return t;
}

void insert(tree_t **tree, int key)
{
    if (*tree == NULL) *tree = new(key);
    else if (key < (*tree)->key) insert(&(*tree)->left, key);
    else if (key > (*tree)->key) insert(&(*tree)->right, key);
}

int find(tree_t *tree, int key)
{
    if (tree == NULL) return 0;
    else if (key < tree->key) return find(tree->left, key);
    else if (key > tree->key) return find(tree->right, key);
    return 1;
}

int main()
{
    tree_t *tree = NULL;
    insert(&tree, 42);
    insert(&tree, 17);
    insert(&tree, 2);
    insert(&tree, 37);
    printf("show tree\n");
    show(tree);
    int key = 37;
    printf("find: %d => %d\n", key, find(tree, key));
}

