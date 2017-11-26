#include "types.h"

void show(tree_t *tree)
{
    printf("key: %d\n", tree->key);
}

tree_t *new(int key)
{
    tree_t *t = malloc(sizeof(tree_t));
    t->left = t->right = NULL;
    t->key = key;
    return t;
}

void insert(tree_t *tree, int key)
{
    if (tree == NULL) {
        tree = new(key);
        return;
    }
    if (key < tree->key) insert(tree->left, key);
    else if (key > tree->key) insert(tree->right, key);
    else return; // no duplicates
}

int main()
{
    tree_t *tree = NULL; //new(42);
    show(tree);
}

