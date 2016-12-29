#include "pch.h"
#include "list.h"

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

    int i;
    for (i = 0; i < 8; i++) {
        list_push(&head, i);
    }
    list_show(&head);
}

int main()
{
    merge_lists();
}

