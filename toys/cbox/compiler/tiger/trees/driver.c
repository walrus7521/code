/* This file is not complete.  You should fill it in with your
   solution to the programming exercise. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/util.h"

// Macros
#define MAX(a, b) (a > b ? a : b)

// Struct definitions
typedef struct tree *T_tree;
struct tree {
    T_tree left;
    string key;
    T_tree right;
};

T_tree Tree(T_tree l, string k, T_tree r)
{
    T_tree t = checked_malloc(sizeof(*t));
    t->left=l; t->key=k; t->right=r;
    return t;
}

T_tree insert(string key, T_tree t)
{
    if (t == NULL) {
        return Tree(NULL, key, NULL);
    } else if (strcmp(key, t->key) < 0) {
        return Tree(insert(key, t->left), t->key, t->right);
    } else if (strcmp(key, t->key) > 0) {
        return Tree(t->left, t->key, insert(key, t->right));
    } else {
        return Tree(t->left, key, t->right);
    }
}

void show(T_tree t)
{
    if (t == NULL) return;
    show(t->left);
    printf("k: %s\n", t->key);
    show(t->right);
}

int member(T_tree t, string key)
{
    if (t == NULL) {
        return 0;
    } else if (strcmp(key, t->key) == 0) {
        return 1;
    } else if (strcmp(key, t->key) < 0) {
        return member(t->left, key);
    } else if (strcmp(key, t->key) > 0) {
        return member(t->right, key);
    }
    return 0;
}

int main()
{
    char *vals[] = {"t","s","p","i","p","f","b","s","t"};
    //char *vals[] = {"a","b","c","d","e","f","g","h","i"};
    int len = sizeof(vals)/sizeof(vals[0]);

    T_tree root = NULL;
    int i;
    for (i = 0; i < len; i++) {
        root = insert(vals[i], root);
    }
    show(root);

    printf("is member: %s ? %d\n", "b", member(root, "b"));
    return 0;
}


