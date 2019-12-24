#include <stdio.h>


typedef struct ll_head {
     struct ll_head *next;
     struct ll_head *prev;
} ll_t;

typedef struct {
     ll_t node;
     size_t size;
     char * block;
} alloc_node_t;

#define ALLOC_HEADER_SZ offsetof(alloc_node_t, block)

int main()
{
}

