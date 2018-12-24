#ifndef _TREE_H_
#define _TREE_H_

typedef struct tree_node tree_node, *tree;

struct tree_node {
    void *datapointer;
    tree left;
    tree right;
};

#define DATA(T)   ((T)->datapointer)
#define LEFT(T)   ((T)->left)
#define RIGHT(T)  ((T)->right)

typedef enum { PREORDER, INORDER, POSTORDER, LEVELORDER } ORDER;

#include "common.h"
#include "stack.h"
#include "tree.h"

status allocate_tree_node(tree *p_T, void *data);
void free_tree_node(tree *p_t);
status init_tree(tree *p_T);
bool empty_tree(tree *p_T);
status make_root(tree *p_T, void *data, tree left, tree right);
void destroy_tree(tree *p_T);
status traverse_tree(tree *p_T, status (*p_func_f)(), ORDER order);
status push_tree(stack *p_S, tree T);
status pop_tree(stack *p_S, tree *p_T);


#endif // _TREE_H_
