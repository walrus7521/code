#include <stdio.h>
#include "adt.h"

// gcc adt.c test_adt.c
//
int main()
{
    foo_t *f = create();
    show(f);
}

