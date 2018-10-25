#ifndef _LIST_H_
#define _LIST_H_

typedef struct _link {
    struct _link *next;
    int value;
} link, list;

link *list_new()
{
    link *n = (link *) malloc(sizeof(link));
    n->next = NULL;
    return n;
}

void push(list *head, int value)
{
    link *n = list_new();
    n->value = value;
    n->next = head->next;
    head->next = n;
}

void list_show(list *head)
{
    link *n;
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %d\n", n->value);
        n = n->next;
    }
    printf("\n");
}

list *list_create(int *a, int n)
{
    int i;
    list *l = list_new();
    for (i = 0; i < n; i++) {
        push(l, a[i]);
    }
    return l;
}

#endif // _LIST_H_

