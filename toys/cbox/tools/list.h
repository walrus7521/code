#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _link {
    struct _link *next, *tail;
    int val;
} link, list;

void show(list *head);
void list_recursive_print(list *head);

link *list_new(int val);
link *list_reverse(list *head);
void list_reverse_r(list** head_ref);
int has_loop(list *l);
link *detect_loop(list *first);
void enqueue(list *head, int x);
link *dequeue(list *head);
int push(list *head, int x);
link *pop(list *head);
list *zip(list *l, list *f);
list *merge(list *h1, list *h2);
list *merge2(list *l, list *f);
void stack();
void fifo();
void merge_sort();
void cycle_test();
void list_recursive_print(list *head);
list *intersection(list *a, list *b);
void test_intersection();
void test_ring();
void test_stk();
void test_reverse();
int list_test();

#endif // _LIST_H_

