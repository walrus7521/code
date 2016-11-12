#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int value;
} link, list;

#define LIST_EMPTY(list) (list->tail == NULL)

link *list_new();
void list_push_back(list *head, int value);
int list_push_front(list *head, int value);
link *list_pop_front(list *head);
link *reverse(list *head);
void list_show(list *head);
list *merge(list *l, list *f);
list *merge2(list *l, list *f);

