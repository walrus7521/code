#include <stdio.h>

typedef int e_v;
#define SIZE_RING 32
#include "ring2.inc"

#define VALID(n) (a[n] == -1 ? 0 : 1)
#define VISITED(n) (vector & (1 << (n)))
#define VISIT(n) (vector |= (1 << (n)))

void test()
{
    int a[] = {1,3,5,7,9,2,4,6,8,-1};
    int len = sizeof(a)/sizeof(a[0]);
    int n;
    unsigned long vector = 0;
    
    printf("len: %d\n", len);
    rngini();

    // prime the pump
    rngput(0);
    VISIT(0);

    while (!rngempty()) {
        n = rngget();
        printf("val: %d\n", a[n]);
        if (VALID(n+1)) {
            if (!VISITED(n+1)) {
                rngput(n+1);
                VISIT(n+1);
            }
        }
    }

}

int main()
{
    test();
}

