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



#endif // __TREE__
