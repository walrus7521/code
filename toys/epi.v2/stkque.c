#include "pch.h"
#include "list.h"

/*
 * fix max --> heap
 *
 */

void set_max(struct list *head, int val)
{
    if (val > head->max) head->max = val;
}

int get_max(struct list *head)
{
    return head->max;
}


int main()
{
    struct list *head = list_create(0);
    list_push(head, 42);
    list_push(head, 67);
    list_put(head, 43);
    list_put(head, 68);
    list_show(head);
    while (!list_empty(head)) {
        printf("pop: %d\n", list_pop(head));
        printf("get: %d\n", list_get(head));
    }
}
