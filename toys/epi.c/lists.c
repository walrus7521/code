#include "pch.h"
#include "list.h"

void test_max_stack()
{
}

void merge_lists()
{
    int ii1[] = {9,7,5,3,1};
    int ii2[] = {42,12,9,7,2};
    int arr[32], i;
    struct heap hp = { .A = arr, .length = 1, .size = 32 };
    struct list head1 = { .next = NULL, .last = NULL, .key = 42, .max = &hp };
    struct list head2 = { .next = NULL, .last = NULL, .key = 42, .max = &hp };
    for (i = 0; i < 5; i++) {
        list_push(&head1, ii1[i]);
        list_push(&head2, ii2[i]);
    }
    list_show(&head1);
    list_show(&head2);
    struct list *head3 = merge_2_sorted_lists(&head1, &head2);
    list_show(head3);
}

void test_list()
{
    int arr[32];
    struct heap hp = { .A = arr, .length = 1, .size = 32 };
    struct list head = { .next = NULL, .last = NULL, .key = 42, .max = &hp };

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
    //merge_lists();
    test_list();
}

