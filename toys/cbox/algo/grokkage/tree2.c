#include <stdio.h>
#include <stdlib.h>

typedef int key_t;
typedef struct tr_n_t {
    key_t key;
    struct tr_n_t *left, *right;
} tree_node_t;

void left_rotation(tree_node_t *root);
void right_rotation(tree_node_t *root);

//#define dprint printf
#define dprint(...)
#define MAX(a,b) (((a)>(b))?(a):(b))


tree_node_t *new(int key) {
    tree_node_t *t = (tree_node_t *) malloc(sizeof(tree_node_t));
    t->left = t->right = NULL;
    t->key = key;
    dprint("creating new node..%d\n", t->key);
    return t;
}

void left_rotation(tree_node_t *n)
{
    tree_node_t  *tmp_node;
    int tmp_key;
    tmp_node = n->left;
    tmp_key = n->key;
    n->left = n->right;
    n->key = n->right->key;
    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left = tmp_node;
    n->left->key = tmp_key;
}

void right_rotation(tree_node_t *n)
{
    tree_node_t  *tmp_node;
    int tmp_key;
    tmp_node = n->right;
    tmp_key = n->key;
    n->right = n->left;
    n->key = n->left->key;
    n->left = n->right->left;
    n->right->left = n->right->right;
    n->right->right = tmp_node;
    n->right->key = tmp_key;
}

tree_node_t *insert(tree_node_t *root, int key)
{
    tree_node_t *t = root;
    if (t == NULL) {
        t = new(key);
        return t;
    } else
    if (key < t->key) {
        t->left  = insert(t->left, key);
    } else if (key >= t->key) {
        t->right = insert(t->right, key);
    }
    return t;
}

tree_node_t *tfind(tree_node_t *root, int key)
{
    if (root == NULL) return NULL;
    if      (root->key < key) tfind(root->right, key);
    else if (root->key >= key) tfind(root->left, key);
    else {
        printf("found it %d\n", root->key);
        return root;
    }
    return NULL;
}

void tshow(tree_node_t *root) 
{
    if (root) {
        tshow(root->left);
        printf("v: %d\n", root->key);
        tshow(root->right);
    }       
}

#define MAX_DEPTH 16
int _print_t(tree_node_t *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
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

int print_t(tree_node_t *tree)
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

int main()
{
    tree_node_t *root = NULL, *t;
    int a[] = {10, 5, 4, 3, 4, 7, 16, 13, 11, 13, 20, 18, 17, 16, 17, 19, 30};
    int i, sz = sizeof(a) / sizeof(a[0]);
    for (i = 0; i < sz; ++i) {
        root = insert(root, a[i]);
    }
    print_t(root);
    return 0;
}

