#include <stdio.h>
#include <stdlib.h>

/* #define dprintf printf */
/* #define dprintf(...) */
enum { BITS_PER_WORD=32, MAX_SIZE=4096 };
unsigned int vector[MAX_SIZE];
int vsize = MAX_SIZE/BITS_PER_WORD+1;

void vclear()
{
    int i;
    for (i = 0; i < vsize; i++) vector[i] = 0;
}

int lookup(int x)
{
    int idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD), mask = (1 << bit);
    int set = (vector[idx] & mask) ? 1 : 0;
    /* dprintf("lookup bit=%x mask=%x => %d:%08X\n", bit, mask, set, vector[idx]); */
    return set;
}

void insert(int x)
{
    int idx = (x / BITS_PER_WORD), bit = (x % BITS_PER_WORD), mask = (1 << bit);
    vector[idx] |= mask;
    /* dprintf("insert bit=%x => [%d]:%08x\n", bit, idx, vector[idx]); */
}

int main()
{
    int is_jolly, n, i, v1, v2;
    while (scanf("%d", &n) != EOF) {
        if (n == 1) {
            printf("Jolly\n");
            scanf("%d", &n);
        } else if (n == 0) printf("Not jolly\n");
        else {
            vclear();
            scanf("%d", &v1);
            for (i = 0; i < n-1; i++) {
                scanf("%d", &v2);
                insert(abs(v2-v1));
                v1 = v2;
            }
            is_jolly = 1;
            for (i = 1; i < n; i++) {
               if (!lookup(i)) {
                   is_jolly = 0;
                   break;
               }
            }
            if (is_jolly) printf("Jolly\n");
            else           printf("Not jolly\n");
        }
    }
    return 0;
}
