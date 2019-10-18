#ifndef __TREE__
#define __TREE__

typedef int key_t;

typedef enum color {
    RED,
    BLACK
} color;

typedef struct node_t node_t;

typedef struct tree_t {
    struct node_t *root;
} tree_t;

typedef struct node_t {
    key_t key;
    int color;
    int level;
    int label;
    struct node_t *p;
    struct node_t *left;
    struct node_t *right;
} node_t;

node_t *create_node(key_t key);
void tree_insert(tree_t *root, node_t *newnode);
node_t *find(tree_t *t, int key);
void tree_delete(tree_t *t, node_t *z);
node_t *tree_min(tree_t *t);
//tree_t *tree_search(tree_t *root, key_t target);
//int *tree_find(tree_t *root, int key);
//void tree_preorder(tree_t *root);
//void tree_inorder(tree_t *root);
//void tree_postorder(tree_t *root);

#define MAX_DEPTH 6
int _print_t(node_t *tree, int is_left, int offset, int depth, char s[MAX_DEPTH][255])
{
    char b[MAX_DEPTH];
    int width = 5;
    int left, right, i;
    if (!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
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
    _print_t(tree->root, 0, 0, 0, s);
    for (i = 0; i < MAX_DEPTH; i++)
        printf("%s\n", s[i]);
    return 0;
}



#endif // __TREE__
