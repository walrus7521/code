#include "common.h"
#include "stack.h"
#include "tree.h"

status allocate_tree_node(tree *p_T, void *data)
{
    tree T = (tree) malloc(sizeof(tree_node));

    if (T == NULL) {
        return ERROR;
    }

    *p_T = T;
    DATA(T) = data;
    LEFT(T) = NULL;
    RIGHT(T) = NULL;

    return OK;
}

void free_tree_node(tree *p_T)
{
    free(*p_T);
    *p_T = NULL;
}

status init_tree(tree *p_T)
{
    *p_T = NULL;
    return OK;
}

bool empty_tree(tree T)
{
    return (T == NULL) ? true : false;
}

status make_root(tree *p_T, void *data, tree left, tree right)
{
    if (empty_tree(*p_T) == false) {
        return ERROR;
    }
    if (allocate_tree_node(p_T, data) == ERROR) {
        return ERROR;
    }

    LEFT(*p_T) = left;
    RIGHT(*p_T) = right;

    return OK;
}

void destroy_tree(tree *p_T, void (*p_func_f)())
{
    if (empty_tree(*p_T) == false) {
        destroy_tree(&LEFT(*p_T), p_func_f);
        destroy_tree(&RIGHT(*p_T), p_func_f);
        if (p_func_f != NULL) {
            (*p_func_f)(DATA(*p_T));
        }
        free_tree_node(p_T);
    }
}

status traverse_tree(tree T, status (*p_func_f)(), ORDER order)
{
    switch (order) {
        case PREORDER:   return preorder_traverse(T, p_func_f);
        case INORDER:    return inorder_traverse(T, p_func_f);
        case POSTORDER:  return postorder_traverse(T, p_func_f);
        case LEVELORDER: return levelorder_traverse(T, p_func_f);
    }
    return ERROR;
}

status preorder_traverse(tree T, status (*p_func_f)())
{
    status rc;
    if (empty_tree(T) == true) {
        return OK;
    }
    rc = (*p_func_f)(DATA(T));
    if (rc == OK) {
        rc = preorder_traverse(LEFT(T), p_func_f);
    }
    if (rc == OK) {
        rc = preorder_traverse(RIGHT(T), p_func_f);
    }
    return rc;
}

status inorder_traverse(tree T, status (*p_func_f)())
{
    status rc;
    if (empty_tree(T) == true) {
        return OK;
    }
    rc = inorder_traverse(LEFT(T), p_func_f);
    if (rc == OK) {
        rc = (*p_func_f)(DATA(T));
    }
    if (rc == OK) {
        rc = inorder_traverse(RIGHT(T), p_func_f);
    }
    return rc;
}

status postorder_traverse(tree T, status (*p_func_f)())
{
    status rc;
    if (empty_tree(T) == true) {
        return OK;
    }
    rc = postorder_traverse(LEFT(T), p_func_f);
    if (rc == OK) {
        rc = postorder_traverse(RIGHT(T), p_func_f);
    }
    if (rc == OK) {
        rc = (*p_func_f)(DATA(T));
    }
    return rc;
}

status levelorder_traverse(tree T, status (*p_func_f)())
{
    return OK;
}


status push_tree(stack *p_S, tree T)
{
    tree *p_T = (tree *) malloc(sizeof(tree));
    if (p_T == NULL) {
        return ERROR;
    }

    *p_T = T;
    if (push(p_S, (void *) p_T) == ERROR) {
        free(p_T);
        return ERROR;
    }

    return OK;
}

status pop_tree(stack *p_S, tree *p_T)
{
    tree *ptr;

    if (pop(p_S, (void **) &ptr) == ERROR) {
        return ERROR;
    }

    *p_T = *ptr;
    free(ptr);

    return OK;
}



