#ifndef __TREE__
#define __TREE__

typedef int key_t;

typedef struct tree_t {
    key_t key;
    int level;
    int label;
    struct tree_t *left;
    struct tree_t *right;
} tree_t;

tree_t *tree_search(tree_t *root, key_t target);
tree_t *tree_insert(tree_t *root, tree_t *newnode);
void tree_preorder(tree_t *root);
void tree_inorder(tree_t *root);
void tree_postorder(tree_t *root);



#endif // __TREE__
