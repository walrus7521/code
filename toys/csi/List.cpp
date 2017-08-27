#include "pch.hpp"

using namespace std;

template <typename T>
class ListNode {
public:
    T data;
    std::shared_ptr<ListNode<T>> next;
};

std::shared_ptr<ListNode<int>> SearchList(std::shared_ptr<ListNode<int>> L, int key) {
    while (L && L->data != key) {
        L = L->next;
    }
    return L;
}

void InsertAfter(const std::shared_ptr<ListNode<int>>& node,
                 const std::shared_ptr<ListNode<int>>& new_node) {
    new_node->next = node->next;
    node->next = new_node;
}

void AppendNode(std::shared_ptr<ListNode<int>> *node,
                std::shared_ptr<ListNode<int>> *tail) {
    (*tail)->next = *node;
    *tail = *node;
    *node = (*node)->next;
}

void DeleteAfter(const std::shared_ptr<ListNode<int>>& node) {
    node->next = node->next->next;
}


template <typename T>
std::shared_ptr<ListNode<T>> MergeSortedListsInPlace(std::shared_ptr<ListNode<T>>& l1, 
                                                     std::shared_ptr<ListNode<T>>& l2)
{
    shared_ptr<ListNode<T>> ret = nullptr;
    shared_ptr<ListNode<T>> m = nullptr;
    shared_ptr<ListNode<T>> n1 = l1->next;
    shared_ptr<ListNode<T>> n2 = l2->next;
    shared_ptr<ListNode<T>> q = nullptr;
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

std::shared_ptr<ListNode<int>> MergeSortedLists(const std::shared_ptr<ListNode<int>>& list1,
                                                const std::shared_ptr<ListNode<int>>& list2) {
    std::shared_ptr<ListNode<int>> merge = std::make_shared<ListNode<int>>();
    auto tail = merge;
    std::shared_ptr<ListNode<int>> p1 = list1->next; // skip head
    std::shared_ptr<ListNode<int>> p2 = list2->next;
    while (p1 && p2) {
        if (p1->data <= p2->data) {
            AppendNode(&p1, &tail);
        } else {
            AppendNode(&p2, &tail);
        }
    }
    if (p1) {
        tail->next = p1;
    } else if (p2) {
        tail->next = p2;
    }
    return merge;
}

template <typename T>
void Reverse(std::shared_ptr<ListNode<T>> head_ref)
{
    shared_ptr<ListNode<T>> rev = nullptr;
    shared_ptr<ListNode<T>> curr = head_ref;
    curr = curr->next;
    shared_ptr<ListNode<T>> rest;
    while (curr != nullptr) {
        rest = curr->next;
        curr->next = rev;
        rev = curr;
        curr = rest;
    }
    curr = head_ref;
    curr->next = rev;
}


template <typename T>
void Reverse_Stack(shared_ptr<ListNode<T>> head_ref)
{
    shared_ptr<ListNode<T>> stack = make_shared<ListNode<T>>();
    stack->next = nullptr; stack->data = -422;

    shared_ptr<ListNode<T>> p = (head_ref)->next;
    while (p) {
        shared_ptr<ListNode<int>> t = make_shared<ListNode<T>>();
        t->next = nullptr; t->data = p->data;
        InsertAfter(stack, t);
        p = p->next;
    }
    p = (head_ref)->next; // reset p
    while (stack->next != nullptr) {
        T data = stack->next->data;
        DeleteAfter(stack);
        p->data = data;
        p = p->next;
    }
}


template <typename T>
void Reverse_Recurse(shared_ptr<ListNode<T>> *head_ref, 
                     shared_ptr<ListNode<T>> *rev,
                     shared_ptr<ListNode<T>> *curr)
{
    if (*curr == nullptr) {
        *curr = *head_ref;
        (*curr)->next = *rev;
        return;
    }
    shared_ptr<ListNode<T>> rest = (*curr)->next;
    (*curr)->next = *rev;
    *rev = *curr;
    *curr = rest;
    Reverse_Recurse(head_ref, rev, curr);
}



void ShowList(const std::shared_ptr<ListNode<int>>& L) {
    std::shared_ptr<ListNode<int>> p = L->next;
    while (p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

#include "pch.hpp"
// node std:: has list (dbl linked list) and forward_list (single linked list)

using namespace std;

void merge_lists()
{
    int ii1[] = {9,7,5,3,1};
    int ii2[] = {16,14,10,6,2};
    shared_ptr<ListNode<int>> head1 = make_shared<ListNode<int>>();
    shared_ptr<ListNode<int>> head2 = make_shared<ListNode<int>>();
    shared_ptr<ListNode<int>> node;
    for (int i = 0; i < 5; ++i) {
        node = make_shared<ListNode<int>>();
        node->data = ii1[i];
        InsertAfter(head1, node);
        node = make_shared<ListNode<int>>();
        node->data = ii2[i];
        InsertAfter(head2, node);
    }
    ShowList(head1);
    ShowList(head2);
    //shared_ptr<ListNode<int>> head3 = MergeSortedLists(head1, head2);
    shared_ptr<ListNode<int>> head3 = MergeSortedListsInPlace(head1, head2);
    ShowList(head3);
}

void reverse_list()
{
    int ii[] = {16,14,10,6,2};
    shared_ptr<ListNode<int>> head = make_shared<ListNode<int>>();
    shared_ptr<ListNode<int>> node;
    for (int i = 0; i < 5; ++i) {
        node = make_shared<ListNode<int>>();
        node->data = ii[i];
        InsertAfter(head, node);
    }
    ShowList(head);
    cout << endl;

    // 1. iterative
    //Reverse(head);

    // 2. stack based
    //Reverse_Stack<int>(head);

    // 3. recursive
    shared_ptr<ListNode<int>> curr = head->next;
    shared_ptr<ListNode<int>> rev = nullptr;
    Reverse_Recurse<int>(&head, &rev, &curr);
     
    ShowList(head);
}


void use_api()
{
    shared_ptr<ListNode<int>> head = make_shared<ListNode<int>>();
    head->data = 42;
    shared_ptr<ListNode<int>> node;
    for (int i = 0; i < 8; ++i) {
        node = make_shared<ListNode<int>>();
        node->data = i;
        InsertAfter(head, node);
    }
    ShowList(head);
    DeleteAfter(head);
    ShowList(head);
}

int main()
{
    //use_api();
    merge_lists();
    //reverse_list();
}

