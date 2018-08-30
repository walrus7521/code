#include <stdio.h>

#define IFF_0(t) t
#define IFF_1(t) t

#define IFF(name, num) IFF_##num(name)


#define num2str(x) str(x)
#define str(x) #x
#define CONST 23


int main()
{
    printf("%s\n", IFF("bart", 1));
    //printf("%s\n", IFF(0));
    puts(num2str(CONST));
    
}
