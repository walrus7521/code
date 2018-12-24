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

#endif // _TREE_H_
