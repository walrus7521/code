#ifndef _List_h_
#define _List_h_

#include "pch.hpp"
#include "Heap.hpp"

using namespace std;


/*
 *
 * iterate, insert, delete
 * single, double linked
 * links and arrays
 * stacks and queues
 *
 */

template <typename T>
struct List {
    List<T> *next;
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
    l->next = nullptr;
    l->key = key;
    l->max = Heap_create<T>(32);
    return l;
}

template <typename T>
void List_push(List<T> *head, T key)
{
    List<T> *n = List_create(key);
    if (head->next == nullptr) {
        head->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    Heap_insert<T>(head->max, key);
}

template <typename T>
T List_pop(List<T> *head)
{
    static T invalid;
    if (head->next == nullptr) {
        return invalid;
    } else {
        List<T> *n = head->next;
        head->next = n->next;
        T key = n->key;
        free(n);
        Heap_extract<T>(head->max, key);
        return key;
    }
}

template <typename T>
void List_reverse_iterate(List<T> **head_ref)
{
    List<T> *rev = nullptr;
    List<T> *curr = *head_ref;
    curr = curr->next;
    List<T> *rest;
    while (curr != nullptr) {
        rest = curr->next;
        curr->next = rev;
        rev = curr;
        curr = rest;
    }
    curr = *head_ref;
    curr->next = rev;
}

template <typename T>
void List_reverse_stack(List<T> **head_ref)
{
    List<T> *stack = List_create<T>(-422);
    List<T> *p = (*head_ref)->next;
    while (p) {
        List_push(stack, p->key);
        p = p->next;
    }
    p = (*head_ref)->next; // reset p
    while (!List_empty(stack)) {
        T key = List_pop(stack);
        p->key = key;
        p = p->next;
    }
}


template <typename T>
void List_reverse_recurse(List<T> **head_ref, 
                          List<T> **rev,
                          List<T> **curr)
{
    if (*curr == nullptr) {
        *curr = *head_ref;
        (*curr)->next = *rev;
        return;
    }
    List<T> *rest = (*curr)->next;
    (*curr)->next = *rev;
    *rev = *curr;
    *curr = rest;
    List_reverse_recurse(head_ref, rev, curr);
}

// http://codinghighway.com/2013/09/14/mastering-recursion/
//      => study
template <typename T>
List<T> *List_reverse_aux(List<T> *origHead, 
                          List<T> **result, 
                          List<T> *curr)
{
    if (curr->next == nullptr) {
        *result = curr;
    } else {
        List_reverse_aux(origHead, result, curr->next)->next = curr;
    }
    if (curr == origHead)
        curr->next = nullptr;
    return curr;
}

template <typename T>
void List_reverse_helper(List<T> *list)
{
    // 1. use a stack
    //List_reverse_stack<T>(&list);

    // 2. iterate
    //List_reverse_iterate<T>(&list);

    // 3. recurse
    //List<int> *curr = list->next;
    //List<int> *rev = nullptr;
    //List_reverse_recurse(&list,  //List<T> **head_ref, 
    //                     &rev, //List<T> **rev,
    //                     &curr); //List<T> **curr)

    // 4. recurse aux
    List<int> *head = list->next;
    List<int> *rev = nullptr;
    List_reverse_aux(head,
                     &rev,
                     head);
    list->next = rev; // <== this was the issue

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
    if (head->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
List<T> *merge_2_sorted_lists(List<T> *l1, List<T> *l2)
{
    List<T> *m = nullptr;
    List<T> *n1 = l1->next;
    List<T> *n2 = l2->next;
    List<T> *q = nullptr;
    List<T> *ret = nullptr;
    while (n1 && n2) {
        if (n1->key <= n2->key) {
            cout << "n1: " << n1->key << endl;
            if (m == nullptr) {
                m = l1;
                ret = m;
            }
            q = n1;
            n1 = n1->next;
            q->next = m->next;
            m->next = q;
        } else {
            cout << "n2: " << n2->key << endl;
            if (m == nullptr) {
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
    cout << "show list:" << endl;
    if (head == nullptr) return; // || head->next == nullptr) return;
    List<T> *p = head->next;
    while (p) {
        cout << "node: " << p->key << endl;
        p = p->next;
    }
}

#endif // _List_h_