#include <stdio.h>

// fsm : finite state machine
// modeled as a graph
//

typedef struct condition {
    int c;
} condition;

typedef int (*exec)(condition); 
typedef struct transition {
    condition cond;
    exec x;
} transition;

typedef struct state {
    transition trans;
} state;


typedef struct fsm {
    state s[8];
} fsm;

int go(condition cond)
{
    printf("transition time: %x\n", cond.c);
    return 0;
}

int main()
{
    fsm sm;
    transition t;
    int i;
    t.x = go;
    t.cond.c = 0x77;
    for (i = 0; i < 8; i++) {
        sm.s[i].trans = t;
    }
    sm.s[0].trans.x(t.cond);
}
