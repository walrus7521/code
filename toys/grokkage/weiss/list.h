#ifndef LIST_H
#define LIST_H

#include "types.h"

typedef struct node node, *list;

struct node {
    generic_ptr datapointer;
    list next;
};

#define DATA(L) ((L)->datapointer)
#define NEXT(L) ((L)->next)

status allocate_node(list *p_L, generic_ptr data);
void free_node(list *p_L);
status delete_node(list *p_L, list node);
status init_list(list *p_L);
bool empty_list(list L);
status append(list *p_L, generic_ptr data);
status insert(list *p_L, generic_ptr data);
status delete(list *p_L, generic_ptr *p_data);

#endif // LIST_H
