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

typedef enum { OK, ERROR } status;


#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

status allocate_tree_node(tree *p_T, void *data);
void free_tree_node(tree *p_t);
status init_tree(tree *p_T);
bool empty_tree(tree *p_T);
status make_root(tree *p_T, void *data, tree left, tree right);
void destroy_tree(tree *p_T);
status traverse_tree(tree *p_T, status (*p_func_f)(), ORDER order);



#endif // _TREE_H_
