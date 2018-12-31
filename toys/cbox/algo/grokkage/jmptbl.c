#include <stdio.h>

typedef void (*proto)(void);

void a(){printf("a\n");}
void b(){printf("b\n");}
void c(){printf("c\n");}

proto tbl[] = {a, b, c};

int main()
{
    int n = sizeof(tbl)/sizeof(tbl[0]);
    int i;
    for (i = 0; i < n; i++) {
        tbl[i]();
    }
}


