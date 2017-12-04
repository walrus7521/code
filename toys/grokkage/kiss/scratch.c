#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int k;
    struct tree *left;
    struct tree *right;
} tree_t;

tree_t *new(int k)
{
    tree_t *t = malloc(sizeof(tree_t));
    t->k = k;
    t->left = t->right = NULL;
    return t;
}

void insert(tree_t **t, int k)
{
    if (*t == NULL) {
        tree_t *n = new(k);
        *t = n;
    } else if (k < (*t)->k) {
        printf("go left: %d\n", k);
        insert(&((*t)->left), k);
    } else if (k > (*t)->k) {
        printf("go right: %d\n", k);
        insert(&((*t)->right), k);
    }
}

void show(tree_t *t)
{
    if (t == NULL) return;
    if (t->left) show(t->left);
    printf("t: %d\n", t->k);
    if (t->right) show(t->right);
}

int main()
{
    tree_t *t = new(0);
    int a[] = {2,1,3,42,5,4,17};
    int len = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < len; i++) {
        insert(&t, a[i]);
    }
    show(t);
}

