#include <stdio.h>
#include <string.h>

#if 0
#include "fifo.h"
int main()
{
    fifo_ptr f = fifo_new(); 
    fifo_put(f, (void *) 0);
    fifo_put(f, (void *) 1);
    fifo_put(f, (void *) 2);
    fifo_put(f, (void *) 3);
    fifo_show(f);
    //fifo_clear(f);
    fifo_show(f);
    while (!fifo_empty(f)) {
        int l = (int) fifo_get(f);
        printf("=> %d\n", l);
    }
}
#endif

#if 0
#include "linalg.h"
int main()
{
    struct vector v = {1,2,3};
    struct matrix m = {{1,2,3},{4,5,6},{7,8,9}};

    vector_show(&v);
    matrix_show(&m);

}
#endif

#if 1
#include "ring.h"
int main()
{
    int i;
    ring_ptr r1 = ring_create(8);
    ring_ptr r2 = ring_create(16);

    for (i = 0; i < 32; i++) {
        if (!ring_full(r1)) {
            ring_push(r1, (void *) i);
        }
        if (!ring_full(r2)) {
            ring_push(r2, (void *) i);
        }
    }

    printf("full : %d\n", ring_full(r1));
    printf("empty: %d\n", ring_empty(r1));
    printf("size : %d\n", ring_size(r1));

    printf("full : %d\n", ring_full(r2));
    printf("empty: %d\n", ring_empty(r2));
    printf("size : %d\n", ring_size(r2));
    
    while (!ring_empty(r1)) {
        printf("shift1: %d\n", ring_shift(r1));
    }

    while (!ring_empty(r2)) {
        printf("shift2: %d\n", ring_shift(r2));
    }

    ring_dump(r1);
    ring_dump(r2);
}
#endif

#if 0
#include "hash.h"
int main()
{
    char key[8];
    int value;
    map_ptr tab = map_new();

    map_insert(tab, "dude", 76);
    map_insert(tab, "dude", 76);
    map_insert(tab, "bart", 77);
    map_insert(tab, "cindy", 78);
    map_insert(tab, "zoey", 79);
    map_insert(tab, "rowdy", 80);

    strcpy(key, "dude");
    if (map_lookup(tab, key, &value)) {
        printf("found: %s -> %d\n", key, value);
    } else {
        printf("not found: %s\n", key);
    }

    iterate(tab);

    if (map_remove(tab, key, &value)) {
        printf("removed %s -> %d\n", key, value);
    }
    if (map_lookup(tab, key, &value)) {
        printf("found: %s -> %d\n", key, value);
    } else {
        printf("not found: %s\n", key);
    }
    map_delete(tab);
    return 0;
}
#endif

