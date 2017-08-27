#ifndef _List_h_
#define _List_h_

#include "pch.hpp"
#define _NO_MAIN_
#include "Heap.cpp"

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
struct ListNode {
    shared_ptr<ListNode<T>> next;
    T data;
    Heap<T> *max;
};

enum {
    INVALID = -1
};

template <typename T>
void List_show(shared_ptr<ListNode<T>> head);

template <typename T>
shared_ptr<ListNode<T>> List_create(T data)
{
    ListNode<T> l = make_shared<ListNode<T>>(); //new ListNode<T>();
    l->next = nullptr;
    l->data = data;
    l->max = Heap_create<T>(32);
    return l;
}

template <typename T>
void List_push(shared_ptr<ListNode<T>> head, T data)
{
    shared_ptr<ListNode<T>> n = List_create(data);
    if (head->next == nullptr) {
        head->next = n;
    } else {
        n->next = head->next;
        head->next = n;
    }
    Heap_insert<T>(head->max, data);
}

template <typename T>
T List_pop(shared_ptr<ListNode<T>> head)
{
    static T invalid;
    if (head->next == nullptr) {
        return invalid;
    } else {
        shared_ptr<ListNode<T>> n = head->next;
        head->next = n->next;
        T data = n->data;
        free(n);
        Heap_extract<T>(head->max, data);
        return data;
    }
}

template <typename T>
void List_reverse_iterate(ListNode<T> **head_ref)
{
    ListNode<T> *rev = nullptr;
    ListNode<T> *curr = *head_ref;
    curr = curr->next;
    ListNode<T> *rest;
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
void List_reverse_stack(shared_ptr<ListNode<T>> *head_ref)
{
    shared_ptr<ListNode<T>> stack = List_create<T>(-422);
    shared_ptr<ListNode<T>> p = (head_ref)->next;
    while (p) {
        List_push(stack, p->data);
        p = p->next;
    }
    p = (*head_ref)->next; // reset p
    while (!List_empty(stack)) {
        T data = List_pop(stack);
        p->data = data;
        p = p->next;
    }
}


template <typename T>
void List_reverse_recurse(ListNode<T> **head_ref, 
                          ListNode<T> **rev,
                          ListNode<T> **curr)
{
    if (*curr == nullptr) {
        *curr = *head_ref;
        (*curr)->next = *rev;
        return;
    }
    ListNode<T> *rest = (*curr)->next;
    (*curr)->next = *rev;
    *rev = *curr;
    *curr = rest;
    List_reverse_recurse(head_ref, rev, curr);
}

// http://codinghighway.com/2013/09/14/mastering-recursion/
//      => study
template <typename T>
ListNode<T> *List_reverse_aux(ListNode<T> *origHead, 
                          ListNode<T> **result, 
                          ListNode<T> *curr)
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
void List_reverse_helper(ListNode<T> *list)
{
    // 1. use a stack
    //List_reverse_stack<T>(&list);

    // 2. iterate
    //List_reverse_iterate<T>(&list);

    // 3. recurse
    //ListNode<int> *curr = list->next;
    //ListNode<int> *rev = nullptr;
    //List_reverse_recurse(&list,  //ListNode<T> **head_ref, 
    //                     &rev, //ListNode<T> **rev,
    //                     &curr); //ListNode<T> **curr)

    // 4. recurse aux
    ListNode<int> *head = list->next;
    ListNode<int> *rev = nullptr;
    List_reverse_aux(head,
                     &rev,
                     head);
    list->next = rev; // <== this was the issue

}

template <typename T>
T List_max(ListNode<T> *head)
{
    int mx = head->max->A[1];
    return mx;
}

template <typename T>
int List_empty(ListNode<T> *head)
{
    if (head->next == nullptr) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
ListNode<T> *merge_2_sorted_lists(ListNode<T> *l1, ListNode<T> *l2)
{
    ListNode<T> *m = nullptr;
    ListNode<T> *n1 = l1->next;
    ListNode<T> *n2 = l2->next;
    ListNode<T> *q = nullptr;
    ListNode<T> *ret = nullptr;
    while (n1 && n2) {
        if (n1->data <= n2->data) {
            cout << "n1: " << n1->data << endl;
            if (m == nullptr) {
                m = l1;
                ret = m;
            }
            q = n1;
            n1 = n1->next;
            q->next = m->next;
            m->next = q;
        } else {
            cout << "n2: " << n2->data << endl;
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
void List_show(ListNode<T> *head)
{
    cout << "show list:" << endl;
    if (head == nullptr) return; // || head->next == nullptr) return;
    ListNode<T> *p = head->next;
    while (p) {
        cout << "node: " << p->data << endl;
        p = p->next;
    }
}

#undef _NO_MAIN_

#endif // _List_h_

#ifndef _NO_MAIN_

#include "pch.hpp"
#define _NO_MAIN_
#include "Heap.cpp"

using namespace std;

void reversal()
{
    int ii[] = {42,12,9,7,2};
    int arr[32] = {0}, i;
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    ListNode<int> head = { .next = nullptr, .data = 42, .max = &hp };
    ListNode<int> *ph = &head;
    for (i = 0; i < 5; i++) {
        List_push(&head, ii[i]);
    }
    List_show(&head);
    List_reverse_helper(&head);
    List_show(&head);
    while (!List_empty(&head)) {
        cout << "pop: " << List_pop(&head) << endl;
    }
}

void merge_lists()
{
    int ii1[] = {9,7,5,3,1};
    int ii2[] = {42,12,9,7,2};
    int arr[32] = {0}, i;
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    ListNode<int> head1 = { .next = nullptr, .data = 42, .max = &hp };
    ListNode<int> head2 = { .next = nullptr, .data = 42, .max = &hp };
    for (i = 0; i < 5; i++) {
        List_push(&head1, ii1[i]);
        List_push(&head2, ii2[i]);
    }
    List_show(&head1);
    List_show(&head2);
    ListNode<int> *head3 = merge_2_sorted_lists(&head1, &head2);
    List_show(head3);
}

void test_list()
{
    int arr[32] = {0};
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    ListNode<int> head = { .next = nullptr, .data = 42, .max = &hp };
    List_push(&head, 67); cout << "max: " << List_max(&head) << endl;
    List_push(&head, 42); cout << "max: " << List_max(&head) << endl;
    List_push(&head, 43); cout << "max: " << List_max(&head) << endl;
    List_push(&head, 68); cout << "max: " << List_max(&head) << endl;
    List_show(&head);

    cout << "ok start pop/getting" << endl;
    Heap_tree(head.max);

    while (!List_empty(&head)) {
        cout << "max: " << List_max(&head) << endl;
        cout << "pop: " << List_pop(&head) << endl;
        Heap_tree(head.max);
        cout << "max: " << List_max(&head) << endl;
        cout << "get: " << List_pop(&head) << endl;
        Heap_tree(head.max);
        cout << "max: " << List_max(&head) << endl;
    }
}

int main()
{
    //merge_lists();
    //test_list();
    reversal();
}

#endif

