#include "list.h"

int main()
{
    list l;
    if (OK == allocate_node(&l, NULL)) {
        printf("success\n");
        free_node(&l);
    } else {
        printf("failed\n");
    }
}
