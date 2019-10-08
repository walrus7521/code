#include <stdio.h>
#include <stdlib.h>
#include "list.h"

stack_t *create_stack(int size)
{ 
    stack_t *st;
    st = (stack_t *) malloc( sizeof(stack_t) );
    st->base = (item_t *) malloc( size * sizeof(item_t) );
    st->size = size;
    st->top = st->base;
    return( st );
}

int stack_empty(stack_t *st)
{ 
    return( st->base == st->top );
}

int push( item_t x, stack_t *st)
{ 
    if ( st->top < st->base + st->size ) { 
        *(st->top) = x; 
        st->top += 1; 
        return( 0 );
    }
    return (-1);
}

item_t pop(stack_t *st)
{ 
    st->top -= 1;
    return( *(st->top) );
}

item_t top_element(stack_t *st)
{ 
    return( *(st->top -1) );
}

void remove_stack(stack_t *st)
{ 
    free( st->base );
    free( st );
}

void test_stack()
{
    int size = 8;
    int i;
    stack_t *st = create_stack(size);
    for (i = 0; i < size; i++) {
        push((item_t) i, st);
    }
    while (!stack_empty(st)) {
        item_t t = pop(st);
        printf("item: %d\n", (int) t);
    }
}

