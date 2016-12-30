#include "pch.hpp"
#include "heap.hpp"
#include "list.hpp"

void merge_lists()
{
    int ii1[] = {9,7,5,3,1};
    int ii2[] = {42,12,9,7,2};
    int arr[32] = {0}, i;
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    List<int> head1 = { .next = NULL, .last = NULL, .key = 42, .max = &hp };
    List<int> head2 = { .next = NULL, .last = NULL, .key = 42, .max = &hp };
    for (i = 0; i < 5; i++) {
        list_push(&head1, ii1[i]);
        list_push(&head2, ii2[i]);
    }
    list_show(&head1);
    list_show(&head2);
    List<int> *head3 = merge_2_sorted_lists(&head1, &head2);
    list_show(head3);
}

void test_list()
{
    int arr[32] = {0};
    Heap<int> hp = { .A = arr, .length = 1, .size = 32 };
    List<int> head = { .next = NULL, .last = NULL, .key = 42, .max = &hp };
    list_push(&head, 67); printf("max: %d\n", list_max(&head));
    list_push(&head, 42); printf("max: %d\n", list_max(&head));
    list_push(&head, 43); printf("max: %d\n", list_max(&head));
    list_push(&head, 68); printf("max: %d\n", list_max(&head));
    list_show(&head);

    printf("ok start pop/getting\n");
    heap_tree(head.max);

    while (!list_empty(&head)) {
        printf("max: %d\n", list_max(&head));
        printf("pop: %d\n", list_pop(&head));
        heap_tree(head.max);
        printf("max: %d\n", list_max(&head));
        printf("get: %d\n", list_get(&head));
        heap_tree(head.max);
        printf("max: %d\n", list_max(&head));
    }
}

int main()
{
    merge_lists();
    //test_list();
}

