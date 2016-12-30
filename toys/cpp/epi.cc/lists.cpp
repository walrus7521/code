#include "pch.hpp"
#include "Heap.hpp"
#include "List.hpp"

void reversal()
{
    int ii[] = {42,12,9,7,2};
    int arr[32] = {0}, i;
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    List<int> head = { .next = nullptr, .key = 42, .max = &hp };
    for (i = 0; i < 5; i++) {
        List_push(&head, ii[i]);
    }
    List_show(&head);
    head.next = List_reverse(&head);
    List_show(&head);
    while (!List_empty(&head)) {
        printf("pop: %d\n", List_pop(&head));
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
    List_push(&head, 67); printf("max: %d\n", List_max(&head));
    List_push(&head, 42); printf("max: %d\n", List_max(&head));
    List_push(&head, 43); printf("max: %d\n", List_max(&head));
    List_push(&head, 68); printf("max: %d\n", List_max(&head));
    List_show(&head);

    printf("ok start pop/getting\n");
    Heap_tree(head.max);

    while (!List_empty(&head)) {
        printf("max: %d\n", List_max(&head));
        printf("pop: %d\n", List_pop(&head));
        Heap_tree(head.max);
        printf("max: %d\n", List_max(&head));
        printf("get: %d\n", List_pop(&head));
        Heap_tree(head.max);
        printf("max: %d\n", List_max(&head));
    }
}

int main()
{
    //merge_lists();
    //test_list();
    reversal();
}

