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

int main()
{
    tree_t *tree = new(42);
    show(tree);
}

