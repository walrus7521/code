#include "list.h"

status allocate_node(list *p_L, generic_ptr data)
{
    list L = (list) malloc(sizeof(node));
    
    if (NULL == L) return ERROR;

    *p_L = L;
    DATA(L) = data;
    NEXT(L) = NULL;

    return OK;
}

void free_node(list *p_L)
{
    free(*p_L);
    *p_L = NULL;
}

status delete_node(list *p_L, list node)
{
    if (true == empty_list(*p_L))
        return ERROR;

    if (*p_L == node)
        *p_L = NEXT(*p_L);
    else {
        list L;
        for (L = *p_L; L != NULL && NEXT(L) != node; L = NEXT(L)) ;

        if (NULL == L)
            return ERROR;
        else
            NEXT(L) = NEXT(node);
    }
    free_node(&node);
    return OK;
}

status init_list(list *p_L)
{
    *p_L = NULL;
    return OK;
}

bool empty_list(list L)
{
    return (NULL == L) ? true : false;
}

status append(list *p_L, generic_ptr data)
{
    list L, tmplist;

    if (ERROR == allocate_node(&L, data))
        return ERROR;

    if (true == empty_list(*p_L))
        *p_L = L;
    else {
        for (tmplist = *p_L; NEXT(tmplist) != NULL; tmplist = NEXT(tmplist)) ;
        NEXT(tmplist) = L;
    }

    return OK;
}

status insert(list *p_L, generic_ptr data)
{
    list L;

    if (ERROR == allocate_node(&L, data))
        return ERROR;
    NEXT(L) = *p_L;
    *p_L = L;

    return OK;
}

status delete(list *p_L, generic_ptr *p_data)
{
    if (empty_list(*p_L))
        return ERROR;

    *p_data = DATA(*p_L);
    return delete_node(p_L, *p_L);
}


