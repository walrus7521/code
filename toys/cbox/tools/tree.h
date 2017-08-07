#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    struct _tree *left, *right;
    int val;
    int height;
} tree;

tree *new(int val);
int theight(tree *root);
tree *max_node(tree *root);
tree *min_node(tree *root);
tree *avl_single_left(tree *root);
tree *avl_single_right(tree *root);
tree *avl_double_left(tree *root);
tree *avl_double_right(tree *root);
tree *insert_bal(tree *root, int val);
tree *insert(tree *root, int val);
tree *delete(tree *root, int val);
int deletemin(tree **pT);
tree *tfind(tree *root, int val);
void bfs(tree *root);
void dfs(tree *root);
void pre_order(tree *root);
void in_order(tree *root);
void post_order(tree *root);
void tshow(tree *root);
int tree_test();

#endif // _TREE_H_

