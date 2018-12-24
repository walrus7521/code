#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

status allocate_tree_node(tree *p_T, void *data)
{
    return OK;
}

void free_tree_node(tree *p_t)
{
}

status init_tree(tree *p_T)
{
    return OK;
}

bool empty_tree(tree *p_T)
{
    return true;
}

status make_root(tree *p_T, void *data, tree left, tree right)
{
    return OK;
}

void destroy_tree(tree *p_T)
{
}

status traverse_tree(tree *p_T, status (*p_func_f)(), ORDER order)
{
    return OK;
}

