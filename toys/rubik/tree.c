#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define exchg(X, Y) { \
    (X) = (X) ^ (Y);  \
    (Y) = (Y) ^ (X);  \
    (X) = (X) ^ (Y); }

typedef struct tree {
    struct tree *left;
    struct tree *right;
    int key;
} tree_t;


void show_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

static int tree_sort_idx = 0;
tree_t *tree_insert(tree_t *root, int key)
{
    tree_t *t = root;
    if (t == NULL) {
        t = (tree_t *) malloc(sizeof(tree_t));
        t->left = t->right = NULL;
        t->key = key;
        return t;
    } else if (key < t->key) {
        t->left = tree_insert(t->left, key);
    } else if (key > t->key) {
        t->right = tree_insert(t->right, key);
    }
    return t;
}
void tree_inorder(tree_t *root, int a[])
{
    static int idx = 0;
    if (root) {
        tree_inorder(root->left, a);
        a[tree_sort_idx++] = root->key;
        tree_inorder(root->right, a);
    }
}
void tree_sort(int a[], int n)
{
    int i;
    tree_t *root = NULL;
    for (i = 0; i < n; i++) {
        root = tree_insert(root, a[i]);
    }
    tree_sort_idx = 0;
    tree_inorder(root, a);
}

int main()
{
    int a[] = {7,2,9,4,3,6,8};
    int n = sizeof(a)/sizeof(a[0]);
    show_array(a, n);
    tree_sort(a, n);
    show_array(a, n);
}


