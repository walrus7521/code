#include <stdio.h>

#define IFF_0(t) t
#define IFF_1(t) t

#define IFF(name, num) IFF_##num(name)


int main()
{
    IFF("bart", 1);
    //printf("%s\n", IFF(0));
}
