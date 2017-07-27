#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int v;
} link, list;

void show(list *head);
void list_recursive_print(list *head);

link *reverse(list *head)
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


link *detect_loop(list *first)
{
    link *fast, *slow, *found;
    fast = slow = first->next;
    while (slow && slow->next && fast && fast->next && fast->next->next) {
        printf("slow => %d, fast => %d\n", slow->v, fast->v);
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            found = fast;
            break;
        }
    }
    return found;
}

void enqueue(list *head, int x)
{
    link *n = (link *) malloc(sizeof(link));
    n->v = x;
    n->tail = n->next = NULL;
    if (head->tail) {
        head->tail->next = n;
        head->tail = n;
    } else {
        n->next = head->next;
        head->next = n;
        head->tail = n;
    }
    //printf("enqueue => %d\n", x);
}

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
    n->v = x;
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

list *zip(list *first, list *second)
{
    return NULL;
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
        if (s1->v < s2->v) {
            enqueue(sx, s1->v);
            s1 = s1->next;
        } else 
        if (s1->v > s2->v) {
            enqueue(sx, s2->v);
            s2 = s2->next;
        } else {
            enqueue(sx, s1->v);
            enqueue(sx, s2->v);
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

void show(list *head)
{
    link *n;
    if (head == NULL) return;
    n = head->next;
    while (n) {
        printf("n => %d\n", n->v);
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

    h->next = reverse(h);
    printf("show reversed stack\n");
    //show(h);
    list_recursive_print(h);
    while (h->next) {
        link *n = pop(h);
        if (n) printf("pop => %d\n", n->v);
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
    h->next = reverse(h);
    printf("show reversed fifo\n");
    show(h);
    while (h->next) {
        link *n = dequeue(h);
        if (n) printf("dequeue => %d\n", n->v);
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
        printf("detected loop @ %d\n", c->v);
    } else {
        printf("no loop detected\n");
    }
    printf("cycle_test - exit\n");
}

void list_recursive_print(list *head)
{
    if (head != NULL) { // base case
        printf ("%d ", head->v);  // print integer data followed by a space
        list_recursive_print(head->next);     // recursive call on the next node
    } else {
        printf("\n");
    }

}

list *intersection(list *a, list *b)
{
    list *m, *n;
    list *p = (list *) malloc(sizeof(list));
    p->tail = p->next = NULL;
    for (m = a->next; m != NULL; m = m->next) {
        for (n = b->next; n != NULL; n = n->next) {
            if (m->v == n->v) {
                enqueue(p, m->v);
            }
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

int main()
{
    //stack();
    //fifo();
    //merge_sort();
    //cycle_test();
    test_intersection();
    return 0;
}

