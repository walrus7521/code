#include <stdio.h>
#include "stack.h"

int main()
{
    Stack_t stk = Stack_new(); // = NULL asserts
    int i;
    for (i = 0; i < 8; i++) {
        Stack_push(stk, (void *) i);
    }
    i = 0;
    while (!Stack_empty(stk)) {
        printf("[%d] => %d\n", i++, (int) Stack_pop(stk));
    }
    printf("stack empty: %d\n", Stack_empty(stk));

}
