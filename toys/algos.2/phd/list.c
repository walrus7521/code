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

void push_back(list *head, int val)
{
    link *n = list_new(val);
    if (head->tail) {
        head->tail->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    head->tail = n;
}

int push_front(list *head, int val)
{
    link *n = list_new(val);
    if (head->next == NULL) head->tail = n;
    head->next = n;
    return 0;
}

link *pop_front(list *head)
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
    list *r = NULL;
    list *p = head->next;
    list *q;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

// http://www.geeksforgeeks.org/write-a-function-to-reverse-the-nodes-of-a-linked-list/
void reverse_r(list** head_ref)
{
    list* first;
    list* rest;
      
    /* empty list */
    if (*head_ref == NULL)
       return;   
 
    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref;  
    rest  = first->next;
 
    /* List has only one node */
    if (rest == NULL)
       return;   
 
    /* reverse the rest list and put the first element at the end */
    reverse_r(&rest);
    first->next->next  = first;  
     
    /* tricky step -- see the diagram */
    first->next  = NULL;          
 
    /* fix the head pointer */
    *head_ref = rest;              
}


/* merge 2 sorted lists: only use nodes in lists, no 
   allocating new nodes, except for a new head
 */
list *merge(list *l, list *f)
{
    list dummy;
    list *m = list_new(-1);
    //list *m = &dummy;
    list *t = m;
    list *p = l->next;
    list *r = f->next;
    while (p && r) {
        if (p->val < r->val) {
            t->next = p;
            p = p->next;
        } else {
            t->next = r;
            r = r->next;
        }
        t = t->next;
    }
    if (p != NULL) {
        t->next = p;
    }
    if (r != NULL) {
        t->next = r;
    }
    return m;
}

list *zip(list *l, list *f)
{
    list dummy;
    list *m = list_new(-1);
    //list *m = &dummy;
    list *t = m;
    list *p = l->next;
    list *r = f->next;
    int alternate = 1;
    while (p && r) {
        if (alternate) {
            t->next = p;
            p = p->next;
        } else {
            t->next = r;
            r = r->next;
        }
        alternate ^= 1;
        t = t->next;
    }
    if (p != NULL) {
        t->next = p;
    }
    if (r != NULL) {
        t->next = r;
    }
    return m;
}

int has_loop(list *l)
{
    list *slow_p = l, *fast_p = l;
    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;
        if (slow_p == fast_p) {
            //removeLoop(slow_p, list);
            return 1; // found loop
        }
    }
    return 0; // no loop
}

typedef int e_v;
#define SIZE_RING 32
#include "ring.inc"
void test_ring()
{
    int i, n;
    init_ring();
    printf("space avail %d\n", rngspace());
    for (i = 0; i < 8; i++) {
        if (!rngfull()) {
            rngput(i);
        }
    }
reload:
    while (!rngempty()) {
        printf("peek: %d\n", rngpeek());
        printf("bytes avail %d\n", rngdata());
        printf("space avail %d\n", rngspace());
        n = rngget();
        printf("n=%d\n", n);
    }
    for (; i < n+8; i++) {
        if (!rngfull()) {
            rngput(i);
        }
    }
    goto reload;
}

#define SIZE_STAK 32
#include "stak.inc"
void test_stk()
{
    int i, n;
    init_stak();
    printf("space avail %d\n", stkspace());
    for (i = 0; i < 8; i++) {
        if (!stkfull()) {
            stkpush(i);
        }
    }
reload:
    printf("here 1...\n");
    while (!stkempty()) {
        printf("peek: %d\n", stkpeek());
        printf("bytes avail %d\n", stkdata());
        printf("space avail %d\n", stkspace());
        n = stkpop();
        printf("n=%d\n", n);
    }
    for (i=0; i < 32; i++) {
        if (!stkfull()) {
            stkpush(i);
        }
    }
    goto reload;
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

