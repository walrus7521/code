#include "pch.h"
#include "list.h"

int main()
{
    struct list *head = list_create(42);
    int i;
    for (i = 0; i < 8; i++) {
        list_push(head, i);
    }
    list_show(head);
}

