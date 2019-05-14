#include <stdio.h>
#include <stdlib.h>
#include "types.h"

list *new(int val)
{
    list *p = (list *) malloc(sizeof(list));
    p->next = NULL;
    p->val = val;
    return p;
}

list *insert(list *head, int val)
{
    list *p = new(val);
    p->next = head->next;
    head->next = p;
}

list *reverse(list *head)
{
    list *p = head->next, *q, *r = NULL;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

void show(list *head)
{
    list *p = head->next;
    while (p) {
        printf("%d\n", p->val);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    list *head = new(0);
    list *t;
    int i;
    for (i = 0; i < 8; i++) {
        insert(head, i);
    }
    show(head);
    head->next = reverse(head);
    show(head);

}

