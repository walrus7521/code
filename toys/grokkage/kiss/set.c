#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/* tree
 */
typedef struct tree {
    struct tree *left;
    struct tree *right;
    char *key;
} tree_t;

typedef char *e_v;
#define SIZE_RING 32
#include "ring.inc"
int head=0,tail=0;
tree_t *ring[32];

int cmp(char *a, char *b)
{
    int less;
    less = strcmp(a, b);
    return less;
}


void show(tree_t *tree) {
    if (tree == NULL) return;
    if (tree->left) show(tree->left);
    printf("key: %s\n", tree->key);
    if (tree->right) show(tree->right);
}

tree_t *new(char *key) {
    tree_t *t = malloc(sizeof(tree_t));
    t->left = t->right = NULL;
    t->key = strdup(key);
    return t;
}

void insert(tree_t **tree, char *key) {
    if (*tree == NULL) *tree = new(key);
    //else if (key < (*tree)->key) insert(&(*tree)->left, key);
    //else if (key > (*tree)->key) insert(&(*tree)->right, key);
    else if (cmp(key,(*tree)->key)<0) insert(&(*tree)->left, key);
    else if (cmp(key,(*tree)->key)>0) insert(&(*tree)->right, key);
}

char *find(tree_t *tree, char *key) {
    if (tree == NULL) return NULL;
    //else if (key < tree->key) return find(tree->left, key);
    //else if (key > tree->key) return find(tree->right, key);
    else if (cmp(key,tree->key)<0) return find(tree->left, key);
    else if (cmp(key,tree->key)>0) return find(tree->right, key);
    else if (cmp(key,tree->key)==0) return key;
}

bool is_member(tree_t *tree, char *key) {
    if (NULL != find(tree, key)) return true;
    return false;
}


tree_t *dup(tree_t *tree) {
    head=0,tail=0;
    tree_t *dup_tree = NULL;
    ring[head++]=tree;
    while (head != tail) {
        tree_t *n = ring[tail++];
        insert(&dup_tree, n->key);
        if (n->left) ring[head++] = n->left;
        if (n->right) ring[head++] = n->right;
    }
    return dup_tree;
}

// need iterative traversal
tree_t *set_union(tree_t *a, tree_t *b) {
    // copy b into set_union_tree
    tree_t *union_tree = dup(b);
    head=0,tail=0;
    ring[head++]=a;
    while (head != tail) {
        tree_t *n = ring[tail++];
        //printf("%s\n", n->key);
        if (!is_member(union_tree, n->key)) {
            insert(&union_tree, n->key);
        }
        if (n->left) ring[head++] = n->left;
        if (n->right) ring[head++] = n->right;
    }
    return union_tree;
}

tree_t *set_intersection(tree_t *a, tree_t *b) {
    tree_t *intersection_tree = NULL;
    head=0,tail=0;
    ring[head++]=a;
    while (head != tail) {
        tree_t *n = ring[tail++];
        if (is_member(b, n->key)) {
            insert(&intersection_tree, n->key);
        }
        if (n->left) ring[head++] = n->left;
        if (n->right) ring[head++] = n->right;
    }
    return intersection_tree;
}

tree_t *set_difference(tree_t *a, tree_t *b) {
    tree_t *difference_tree = NULL;
    head=0,tail=0;
    ring[head++]=a;
    while (head != tail) {
        tree_t *n = ring[tail++];
        if (!is_member(b, n->key)) {
            insert(&difference_tree, n->key);
        }
        if (n->left) ring[head++] = n->left;
        if (n->right) ring[head++] = n->right;
    }
    head=0,tail=0;
    ring[head++]=b;
    while (head != tail) {
        tree_t *n = ring[tail++];
        if (!is_member(a, n->key)) {
            insert(&difference_tree, n->key);
        }
        if (n->left) ring[head++] = n->left;
        if (n->right) ring[head++] = n->right;
    }
    return difference_tree;
}

int main() {
    tree_t *a = NULL;
    insert(&a, "bart");
    insert(&a, "grant");
    insert(&a, "chad");
    insert(&a, "alex");
    insert(&a, "rowdy");
    tree_t *b = NULL;
    insert(&b, "rowdy");
    insert(&b, "cindy");
    insert(&b, "mackenzie");
    insert(&b, "taylor");
    insert(&b, "claire");
    printf("show a\n");
    show(a);
    printf("show b\n");
    show(b);
    tree_t *c = set_union(a, b);
    printf("union:\n");
    show(c);
    tree_t *d = set_intersection(a, b);
    printf("intersection:\n");
    show(d);
    tree_t *e = set_difference(a, b);
    printf("difference:\n");
    show(e);
    char *key = "mackenzie";
    printf("find: %s => %s\n", key, find(c, key));
}

