#include <stdio.h>
#include <stdlib.h>

#include "list.h"


link *list_new(int val)
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    n->val = val;
    return n;
}

link *list_reverse(list *head)
{
    link *r, *p1, *p2;
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


// http://www.geeksforgeeks.org/write-a-function-to-reverse-the-nodes-of-a-linked-list/
void list_reverse_r(list** head_ref)
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
    list_reverse_r(&rest);
    first->next->next  = first;  
     
    /* tricky step -- see the diagram */
    first->next  = NULL;          
 
    /* fix the head pointer */
    *head_ref = rest;              
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

link *detect_loop(list *first)
{
    link *fast, *slow, *found;
    fast = slow = first->next;
    while (slow && slow->next && fast && fast->next && fast->next->next) {
        printf("slow => %d, fast => %d\n", slow->val, fast->val);
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            found = fast;
            break;
        }
    }
    return found;
}

// goes to tail
void enqueue(list *head, int x)
{
    link *n = (link *) malloc(sizeof(link));
    n->val = x;
    n->tail = n->next = NULL;
    if (head->tail) {
        head->tail->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    head->tail = n;
    //printf("enqueue => %d\n", x);
}

// pop_front and dequeue are identical
//link *pop_front(list *head)
link *dequeue(list *head)
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

int push(list *head, int x)
{
    link *n = (link *) malloc(sizeof(link));
    n->val = x;
    n->next = NULL;
    n->next = head->next;
    head->next = n;
    printf("push => %d\n", x);
    return 0;
}

link *pop(list *head)
{
    link *n = NULL;
    if (head->next) {
        n = head->next;
        head->next = n->next;
    }
    return n;
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


list *merge(list *h1, list *h2)
/* input lists are sorted
 */
{
    link *sx = NULL;
    link *s1, *s2;
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;
    sx = (link *) malloc(sizeof(link));
    sx->tail = sx->next = NULL;
    s1 = h1->next;
    s2 = h2->next;
    while (s1 && s2) {
        if (s1->val < s2->val) {
            enqueue(sx, s1->val);
            s1 = s1->next;
        } else 
        if (s1->val > s2->val) {
            enqueue(sx, s2->val);
            s2 = s2->next;
        } else {
            enqueue(sx, s1->val);
            enqueue(sx, s2->val);
            s1 = s1->next;
            s2 = s2->next;
        }
    }
    if (s1 && !s2) {
        sx->tail->next = s1;
    } else
    if (s2 && !s1) {
        sx->tail->next = s2;
    }
    return sx;
}

/* merge 2 sorted lists: only use nodes in lists, no 
   allocating new nodes, except for a new head
 */
list *merge2(list *l, list *f)
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

void show(list *head)
{
    link *n;
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %d\n", n->val);
        n = n->next;
    }
}

void stack()
{
    list *h = (list *) malloc(sizeof(list));
    h->tail = h->next = NULL;
    printf("stack - enter\n");
    push(h, 7);
    push(h, 5);
    push(h, 4);
    push(h, 3);
    printf("show stack\n");
    //show(h);
    list_recursive_print(h);

    h->next = list_reverse(h);
    printf("show reversed stack\n");
    //show(h);
    list_recursive_print(h);
    while (h->next) {
        link *n = pop(h);
        if (n) printf("pop => %d\n", n->val);
    }
    printf("stack - exit\n");
}

void fifo()
{
    list *h = (list *) malloc(sizeof(list));
    h->tail = h->next = NULL;
    printf("fifo - enter\n");
    enqueue(h, 0);
    enqueue(h, 1);
    enqueue(h, 2);
    enqueue(h, 3);
    printf("show fifo\n");
    show(h);
    h->tail = h->next; /* prep for reversal, fix up tail */
    h->next = list_reverse(h);
    printf("show reversed fifo\n");
    show(h);
    while (h->next) {
        link *n = dequeue(h);
        if (n) printf("dequeue => %d\n", n->val);
    }
    printf("fifo - exit\n");
}

void merge_sort()
{
    list *s1 = (list *) malloc(sizeof(list));
    list *s2 = (list *) malloc(sizeof(list));
    list *sx = NULL;
    printf("merge_sort - enter\n");
    s1->tail = s1->next = NULL;
    s2->tail = s2->next = NULL;
    enqueue(s1, 0);
    enqueue(s1, 2);
    enqueue(s1, 4);
    enqueue(s1, 6);
    printf("show s1\n");
    show(s1);
    enqueue(s2, 1);
    enqueue(s2, 3);
    enqueue(s2, 5);
    enqueue(s2, 7);
    printf("show s2\n");
    show(s2);
    sx = merge(s1, s2);
    printf("show sx\n");
    show(sx);
    printf("merge_sort - exit\n");
}

void cycle_test()
{
    int i;
    list *h = (list *) malloc(sizeof(list));
    list *c = NULL;
    h->tail = h->next = NULL;
    printf("cycle_test - enter\n");
    for (i = 0; i < 8; i++) {
        if (i == 4) c = h->tail;
        enqueue(h, i);
    }
    //h->tail->next = c; // this creates the loop
    if ((c = detect_loop(h))) {
        printf("detected loop @ %d\n", c->val);
    } else {
        printf("no loop detected\n");
    }
    printf("cycle_test - exit\n");
}

void list_recursive_print(list *head)
{
    if (head != NULL) { // base case
        printf ("%d ", head->val);  // print integer data followed by a space
        list_recursive_print(head->next);     // recursive call on the next node
    } else {
        printf("\n");
    }

}

// hack -- use an array as a hasher
// makes it O(n)
list *intersection(list *a, list *b)
{
    int ahash[10000] = {0};
    list *m, *n;
    list *p = (list *) malloc(sizeof(list));
    p->tail = p->next = NULL;
    for (m = a->next; m != NULL; m = m->next) {
        ahash[m->val]++;
    }
    for (n = b->next; n != NULL; n = n->next) {
        if (ahash[n->val]) {
            enqueue(p, n->val);
        }
    }
    return p;
}

void test_intersection()
{
    int i;
    list *a = (list *) malloc(sizeof(list));
    a->tail = a->next = NULL;
    list *b = (list *) malloc(sizeof(list));
    b->tail = b->next = NULL;
    for (i = 0; i < 8; i++) {
        enqueue(a, i);
    }
    for (i = 4; i < 16; i++) {
        enqueue(b, i);
    }
    printf("list a: \n"); show(a); printf("\n");
    printf("list b: \n"); show(b); printf("\n");
    list *c = intersection(a,b);
    printf("list c: (a intersect b)\n"); show(c); printf("\n");

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

void test_reverse()
{
    int i;
    list *l = list_new(-1);
    for (i = 0; i < 8; i++) {
        enqueue(l, i);
        //push_back(l, i);
        //push_front(l, i+16);
    }
    printf("show the list...\n");
    show(l);
    printf("reverse: \n");
    l->next = list_reverse(l);
    //reverse_r(&l);
    printf("show the reversed list...\n");
    show(l);
}

int list_test()
{
    //test_stk();
    //test_ring();
    //stack();
    //fifo();
    //merge_sort();
    //cycle_test();
    //test_intersection();
    test_reverse();
    //
    //
    return 0;
}

