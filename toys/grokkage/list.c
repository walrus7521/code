#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int key;
} link, list;

void list_recursive_print(list *head);

link *list_new(int key)
{
    link *n = (link *) malloc(sizeof(link));
    n->next = n->tail = NULL;
    n->key = key;
    return n;
}

link *list_reverse_pqr(list *head)
{
    link *p = head->next;
    link *q;
    link *r = NULL;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}

link *list_reverse_qr(list *p)
{
    link *q;
    link *r = NULL;
    while (p->next) {
        q = p->next->next;
        p->next->next = r;
        r = p->next;
        p->next = q;
    }
    return r;
}

// http://www.geeksforgeeks.org/write-a-function-to-reverse-the-nodes-of-a-linked-list/
void list_reverse_r(list** head_ref)
{
    list* first;
    list* rest;
      
    /* empty list */
    if (*head_ref == NULL) return;   
 
    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref;  
    rest  = first->next;
 
    /* List has only one node */
    if (rest == NULL) return;   
 
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
    int cycles = 0;
    int loop_found = 0;
    link *fast, *slow, *found;
    fast = slow = first->next;
    while (slow && fast && fast->next) {
        printf("slow => %d, fast => %d\n", slow->key, fast->key);
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) { // found loop
            loop_found = fast->key;
            found = fast;
            printf("loop found in %d cycles\n", cycles);
            break;
        }
        cycles++;
    }
    return found;
}

link *detect_loop2(list *first)
{
    link *fast, *slow, *found;
    fast = slow = first->next;
    while (slow && slow->next && fast && fast->next && fast->next->next) {
        printf("slow => %d, fast => %d\n", slow->key, fast->key);
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
    n->key = x;
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
    n->key = x;
    n->next = NULL;
    n->next = head->next;
    head->next = n;
    printf("push => %d\n", x);
    return 0;
}

int pop(list *head)
{
    int key;
    link *n = NULL;
    if (head->next) {
        n = head->next;
        head->next = n->next;
    }
    key = n->key;
    free(n);
    printf("pop => %d\n", key);
    return key;
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
        if (s1->key < s2->key) {
            enqueue(sx, s1->key);
            s1 = s1->next;
        } else 
        if (s1->key > s2->key) {
            enqueue(sx, s2->key);
            s2 = s2->next;
        } else {
            enqueue(sx, s1->key);
            enqueue(sx, s2->key);
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
        if (p->key < r->key) {
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

void show(list *head, char *name)
{
    link *n;
    printf("show: %s\n", name);
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %d\n", n->key);
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
    show(h, "stack");
    list_recursive_print(h);

    h->next = list_reverse_qr(h);
    printf("show reversed stack\n");
    //show(h, "stack");
    list_recursive_print(h);
    while (h->next) {
        int key = pop(h);
        printf("pop => %d\n", key);
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
    show(h, "fifo");
    h->tail = h->next; /* prep for reversal, fix up tail */
    h->next = list_reverse_qr(h);
    show(h, "reversed fifo");
    while (h->next) {
        link *n = dequeue(h);
        if (n) printf("dequeue => %d\n", n->key);
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
    show(s1, "show s1");
    enqueue(s2, 1);
    enqueue(s2, 3);
    enqueue(s2, 5);
    enqueue(s2, 7);
    show(s2, "show s2");
    sx = merge(s1, s2);
    show(sx, "show sx");
    printf("merge_sort - exit\n");
}

void show_circular(list *h, char *name)
{
    link *n;
    printf("list: %s\n", name);
    if (h == NULL) return;
    n = h;
    int i = 0;
    while (n->next != h) {
        printf("n[%d]:%d\n", i, n->key);
        n = n->next;
        i++;
    }
    printf("n[%d]:%d\n", i, n->key);
}

void josephus()
{
    /* M=5, N=9: 5 1 7 4 3 6 9 2 8 */
    int i, M=4, N=9;
    list *t, *x;
    /* create circular list */
    t = (list *) malloc(sizeof(list));
    t->key = 1; 
    x = t;
    printf("insert:%d\n", x->key);
    for (i = 2; i <= N; i++) {
        t->next = (list *) malloc(sizeof(list));
        t->next->key = i;
        printf("insert:%d\n", t->next->key);
        t->next->next = NULL;
        t = t->next;
    }
    t->next = x; // this creates the loop
    show_circular(x, "josephus");
    t = x;
    while (t->next != x) {
        for (i = 1; i < M; i++) t = t->next;
        printf("die: %d\n", t->next->key);
        x = t->next;
        t->next = x->next;
        free(x);
        t = t->next;
    }
}

void convert_infix_to_postfix()
{
    char c;
    list *stack = (list *) malloc(sizeof(list));
    for (; scanf("%1c", &c) != EOF; ) {
        if (c == ')') printf("%1c", (char) pop(stack));
        if (c == '+') push(stack, (int) c);
        if (c == '*') push(stack, (int) c);
        while (c >= '0' && c <= '9') {
            printf("%1c", c);
            scanf("%1c", &c);
        }
        if (c != '(') printf("");
    }
    printf("\n");
}

void eval_postfix()
{
    char c;
    int x;
    list *stack = (list *) malloc(sizeof(list));
    for (; scanf("%c", &c) != EOF; ) {
        x = 0;
        if (c == '+') x = pop(stack) + pop(stack);
        if (c == '*') x = pop(stack) * pop(stack);
        while (c >= '0' && c <= '9') {
            x = 10 * x + (c - '0');
            scanf("%c", &c);
        }
        push(stack, x);
    }
    printf("%d\n", x);
}

void cycle_test()
{
    int i, v;
    list *h = (list *) malloc(sizeof(list));
    list *c = NULL;
    h->tail = h->next = NULL;
    printf("cycle_test - enter\n");
    for (i = 0; i < 8; i++) {
        if (i == 4) c = h->tail; // pick a spot to splice
        enqueue(h, i);
    }
    h->tail->next = c; // this creates the loop
    if ((c = detect_loop(h))) {
    //if (v = detect_loop(h)) {
        printf("detected loop @ %d\n", c->key);
        //printf("detected loop @ %d\n", v);
    } else {
        printf("no loop detected\n");
    }
    printf("cycle_test - exit\n");
}

void list_recursive_print(list *head)
{
    if (head == NULL) return;
    list *n = head->next;
    if (n != NULL) { // base case
        printf ("%d ", n->key);  // print integer data followed by a space
        list_recursive_print(n);     // recursive call on the next node
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
        ahash[m->key]++;
    }
    for (n = b->next; n != NULL; n = n->next) {
        if (ahash[n->key]) {
            enqueue(p, n->key);
        }
    }
    return p;
}

// this finds the 1st node that 2 lists point to simultaneously
void test_intersect2()
{
    list *a = (list *) malloc(sizeof(list));
    list *aa = a;
    a->next = (link *) malloc(sizeof(link)); a->next->key = 1; a->next = a->next->next;
    a->next = (link *) malloc(sizeof(link)); a->next->key = 2; a->next = a->next->next;
    a->next = (link *) malloc(sizeof(link)); a->next->key = 3; a->next = a->next->next;
    a->next = (link *) malloc(sizeof(link)); a->next->key = 4; a->next = a->next->next;
    a->next = NULL;
    list *b = (list *) malloc(sizeof(list));
    list *bb = b;
    b->next = (link *) malloc(sizeof(link)); b->next->key = 5; b->next = b->next->next;
    b->next = (link *) malloc(sizeof(link)); b->next->key = 6; b->next = b->next->next;
    b->next = a->next; a->next = a->next->next;
    a->next = (link *) malloc(sizeof(link)); a->next->key = 7; a->next = a->next->next;
    b->next = NULL;

    show(aa, "show list aa"); printf("\n");
    show(bb, "show list bb"); printf("\n");
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
    enqueue(a, 42);
    for (i = 4; i < 16; i++) {
        enqueue(b, i);
    }
    enqueue(b, 42);
    show(a, "list a"); printf("\n");
    show(b, "list b"); printf("\n");
    list *c = intersection(a,b);
    show(c, "list c (a intersect b)"); printf("\n");
    list_recursive_print(c->next);

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
    show(l, "show the list");
    printf("reverse: \n");
    //l->next = list_reverse_pqr(l);
    l->next = list_reverse_qr(l);
    //reverse_r(&l);
    show(l, "show the reversed list...");
}

int main()
{
    //test_stk();
    //test_ring();
    //stack();
    fifo();
    //merge_sort();
    //cycle_test();
    //test_intersection();
    //test_intersect2();
    //test_reverse();
    //josephus();
    //convert_infix_to_postfix();
    //eval_postfix();
    //
    //
    return 0;
}

