#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    char *value;
} link, list;

#define LIST_EMPTY(list) (list->tail == NULL)

link *list_new()
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    return n;
}

void list_push_back(list *head, char *value)
{
    link *n = list_new();
    n->value = value;
    n->tail = n->next = NULL;
    if (head->tail) {
        head->tail->next = n;
        head->tail = n;
    } else {
        n->next = head->next;
        head->next = n;
        head->tail = n;
    }
}

int list_push_front(list *head, char *value)
{
    link *n = list_new();
    n->value = value;
    n->next = head->next;
    if (head->next == NULL) head->tail = n;
    head->next = n;
    return 0;
}

link *list_pop_front(list *head)
{
    link *n = NULL;
    if (head->tail) {
        n = head->next;
        if (head->next == head->tail) {
            head->next = NULL;
            head->tail = NULL;
        } else {
            head->next = n->next;
        }
    }
    return n;
}

link *reverse(list *head)
{
    list *r, *p1, *p2;
    r = NULL;
    p1 = head->next;
    while (p1) {
        p2 = p1->next;
        p1->next = r;
        r = p1;
        p1 = p2;
    }
    return r;
}

void list_show(list *head)
{
    link *n;
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %s\n", n->value);
        n = n->next;
    }
    printf("\n");
}

#if 0
int main()
{
    int i;
    list *l = list_new();
    list *r = list_new();
    for (i = 0; i < 8; i++) {
        list_push_back(l, i);
        list_push_front(l, i+16);
    }
    list_show(l);
    r->next = reverse(l);
    list_show(r);
    return 0;
    while (!LIST_EMPTY(l)) {
        link *n = list_pop_front(l);
        printf("pop: %d\n", n->value);
    }
    return 0;
}
#endif
