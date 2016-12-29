#include "pch.h"
#include "list.h"

int main()
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

