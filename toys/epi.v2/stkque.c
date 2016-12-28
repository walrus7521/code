#include "pch.h"
#include "list.h"

/*
 * fix max --> heap
 *
 */
#if 0
void set_max(struct list *head, int val)
{
    if (val > head->max) head->max = val;
}

int get_max(struct list *head)
{
    return head->max;
}
#endif

int main()
{
    struct list *head = list_create(0);
    list_push(head, 67);
    printf("show max: %d\n", list_max(head));
    list_push(head, 42);
    printf("show max: %d\n", list_max(head));
    list_put(head, 43);
    printf("show max: %d\n", list_max(head));
    list_put(head, 68);
    printf("show max: %d\n", list_max(head));
    list_show(head);
    printf("ok start pop/getting\n");
    heap_tree(head->max);
    while (!list_empty(head)) {
        printf("show max: %d\n", list_max(head));
        printf("pop: %d\n", list_pop(head));
        heap_tree(head->max);
        printf("show max: %d\n", list_max(head));
        printf("get: %d\n", list_get(head));
        heap_tree(head->max);
        printf("show max: %d\n", list_max(head));
    }
}
