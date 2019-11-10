#include "types.h"

list_t *new(int val)
{
    list_t *p = (list_t *) malloc(sizeof(list_t));
    p->next = NULL;
    p->val = val;
    return p;
}

void /* list_t * */insert(list_t *head, int val)
{
    list_t *p = new(val);
    p->next = head->next;
    head->next = p;
}

list_t *reverse(list_t *head)
{
    list_t *p = head->next, *q, *r = NULL;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

void show(list_t *head)
{
    list_t *p = head->next;
    while (p) {
        printf("%d\n", p->val);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    list_t *head = new(0);
    list_t *t;
    int i;
    for (i = 0; i < 8; i++) {
        insert(head, i);
    }
    show(head);
    head->next = reverse(head);
    show(head);

}

