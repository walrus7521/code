#include "pch.hpp"
#include "Heap.hpp"
#include "List.hpp"

using namespace std;

void reversal()
{
    int ii[] = {42,12,9,7,2};
    int arr[32] = {0}, i;
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    List<int> head = { .next = nullptr, .key = 42, .max = &hp };
    List<int> *ph = &head;
    for (i = 0; i < 5; i++) {
        List_push(&head, ii[i]);
    }
    List_show(&head);
    //head.next = List_reverse(&head);
    List_reverse_i(&ph);
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
    List<int> head1 = { .next = nullptr, .key = 42, .max = &hp };
    List<int> head2 = { .next = nullptr, .key = 42, .max = &hp };
    for (i = 0; i < 5; i++) {
        List_push(&head1, ii1[i]);
        List_push(&head2, ii2[i]);
    }
    List_show(&head1);
    List_show(&head2);
    List<int> *head3 = merge_2_sorted_lists(&head1, &head2);
    List_show(head3);
}

void test_list()
{
    int arr[32] = {0};
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    List<int> head = { .next = nullptr, .key = 42, .max = &hp };
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

