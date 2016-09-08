#include <stdio.h>

#define FUNC1(a, b) ({ \
    func1(a, b); \
        })


int func1(int a, int *b) {
    printf("func1: %d %d\n", a, *b);
    *b = 42;
    return a + *b;
}

int main()
{
    int a, b, ret;
    a = 4;
    b = 5;
    ret = func1(a, &b);
    printf("called func1: ret:(%d) a:(%d) b:(%d)\n", ret, a, b);
    a = 9;
    b = 3;
    ret = FUNC1(a, &b);
    printf("called FUNC1: ret:(%d) a:(%d) b:(%d)\n", ret, a, b);
}
