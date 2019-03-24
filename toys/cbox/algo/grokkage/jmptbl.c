#include <stdio.h>

typedef void (*proto)(void);

void a(){printf("a\n");}
void b(){printf("b\n");}
void c(){printf("c\n");}
void r(){printf("r\n");}
void t(){printf("t\n");}

proto tbl[] = {b, a, r, t};

int main()
{
    int n = sizeof(tbl)/sizeof(tbl[0]);
    int i;
    for (i = 0; i < n; i++) {
        tbl[i]();
    }
}


