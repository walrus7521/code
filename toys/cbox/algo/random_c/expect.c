#include <stdio.h>

enum state {
    stopped = 'STOP',
    running = 'RUN!',
    waiting = 'WAIT',
};

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

//see: http://kerneltrap.org/node/4705

//What I like about this is that it also adds some expressiveness to some functions.

void foo(int arg)
{
    printf("%d\n", WAIT);
    if (unlikely(arg == 0)) {
        printf("%d\n", STOP);
        return;
    }
    printf("%d\n", RUN);
}

int main()
{
    foo(0);
}
