#ifndef _List_h_
#define _List_h_

#include "pch.hpp"
#include "Heap.hpp"

template <typename T>
struct List {
    List<T> *next;
    List<T> *last;
    T key;
    Heap<T> *max;
};

enum {
    INVALID = -1
};

template <typename T>
void List_show(List<T> *head);

template <typename T>
List<T> *List_create(T key)
{
    List<T> *l = new List<T>();
    l->next = NULL;
    l->key = key;
    l->max = Heap_create<T>(32);
    return l;
}

template <typename T>
void List_push(List<T> *head, T key)
{
    List<T> *n = List_create(key);
    if (head->next == NULL) {
        head->next = head->last = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    Heap_insert<T>(head->max, key);

}

template <typename T>
void List_put(List<T> *head, T key)
{
    List<T> *n = List_create(key);
    if (head->last == NULL) {
        head->next = head->last = n;
    } else {
        head->last->next = n;
        head->last = n;
    }
    Heap_insert<T>(head->max, key);
}

template <typename T>
T List_pop(List<T> *head)
{
    if (head->next == NULL) {
        return INVALID;
    } else {
        List<T> *n = head->next;
        head->next = n->next;
        int key = n->key;
        free(n);
        Heap_extract<T>(head->max, key);
        return key;
    }
}

template <typename T>
T List_get(List<T> *head)
{
    T key = INVALID;
    List<T> *n = head->next;
    if (head->next == NULL) {
        return key;
    } else
    if (head->next->next == NULL) {
        key = n->key;
        free(n);
        head->next = head->last = NULL;
        return key;
    } else { 
        // find 2nd to last node
        while (n->next->next != NULL) {
            n = n->next;
        }
        List<T> *r = head->last;
        head->last = n;
        n->next = NULL;
        key = r->key;
        free(r);
        Heap_extract<T>(head->max, key);
        return key;
    }
}

template <typename T>
T List_reverse(List<T> *head)
{
}

template <typename T>
T List_max(List<T> *head)
{
    int mx = head->max->A[1];
    return mx;
}

template <typename T>
int List_empty(List<T> *head)
{
    if (head->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
List<T> *merge_2_sorted_lists(List<T> *l1, List<T> *l2)
{
    List<T> *m = NULL;
    List<T> *n1 = l1->next;
    List<T> *n2 = l2->next;
    List<T> *q = NULL;
    List<T> *ret = NULL;
    while (n1 && n2) {
        if (n1->key <= n2->key) {
            printf("n1: %d\n", n1->key);
            if (m == NULL) {
                m = l1;
                ret = m;
            }
            q = n1;
            n1 = n1->next;
            q->next = m->next;
            m->next = q;
        } else {
            printf("n2: %d\n", n2->key);
            if (m == NULL) {
                m = l2;
                ret = m;
            }
            q = n2;
            n2 = n2->next;
            q->next = m->next;
            m->next = q;
        }
        m = m->next;
    }
    if (n1) {
        m->next = n1;
    } else if (n2) {
        m->next = n2;
    }
    return ret;
}

template <typename T>
void List_show(List<T> *head)
{
    printf("show list:\n");
    if (head->next == NULL) return;
    List<T> *p = head->next;
    while (p) {
        printf("node: %d\n", p->key);
        p = p->next;
    }
}

#endif // _List_h_
