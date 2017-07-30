#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int val;
} link, list;

#define LIST_EMPTY(list) (list->tail == NULL)

void list_show(list *head)
{
    if (head == NULL) return;
    link *n = head->next;
    while (n) {
        printf("n => %d\n", n->val);
        n = n->next;
    }
    printf("\n");
}

link *list_new(int val)
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    n->val = val;
    return n;
}

void push_back_no_tail(list *head, int val)
{
    link *n = list_new(val);
    if (head->next == NULL) {
        head->next = n;
    } else {
        link *p;
        for (p = head; p->next != NULL; p = p->next) {
            ;
        }
        p->next = n;
    }
}


int main()
{
#if 0
    // test merge
    list *l = list_new(-1);
    list *f = list_new(-1);
    int i;
    for (i = 0; i < 8; i++) {
        push_back(l, 2*i);
        push_back(f, (2*i+1));
    }
    list_show(l);
    list_show(f);
    //printf("merge: \n");
    //list *m = merge(l, f);
    printf("zip: \n");
    list *z = zip(l, f);
    list_show(z);
    // create a loop
    //l->next->next->next->next->next = l->next->next;
    //printf("loop? %d\n", has_loop(l));
#endif
#if 1
    int i;
    list *l = list_new(-1);
    list *r = list_new(-1);
    for (i = 0; i < 8; i++) {
        push_back(l, i);
        //push_front(l, i+16);
    }
    printf("show the list...\n");
    list_show(l);
    printf("reverse: \n");
    //l->next = reverse(l);
    reverse_r(&l);
    printf("show the reversed list...\n");
    list_show(l);

    while (!LIST_EMPTY(l)) {
        link *n = pop_front(l);
        printf("pop: %d\n", n->val);
    }
#endif
    //test_stk();
    //test_ring();
    return 0;
}

