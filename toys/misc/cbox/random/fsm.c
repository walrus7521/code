#include <stdio.h>
#include <stdlib.h>

// fsm : finite state machine
// modeled as a graph
//

// this is a condition or event
// that results in a transition from
// a given state to another state
//
// conditions may actually be exlusive
// to the states themselves, like global
// events
//
// however, states need to know how to
// respond to a condition, which is why
// I have encoded it this way.
//
// maybe a hash map of events -> states

#define A 0x41
#define B 0x42
#define C 0x43

struct STATE;
typedef struct CONDITION {
    int event;
    struct STATE *state;
} CONDITION;

typedef int (*exec)(int); 
typedef struct TRANSITION {
    CONDITION cond;
    struct STATE *s;
    exec x;
} TRANSITION;

typedef struct STATE {
    TRANSITION *trans;
} STATE;

typedef struct FSM {
    int current;
    STATE s[4];
} FSM;

int go0(int event)
{
    printf("%c", event);
    switch (event) {
        case A: return 1;
        case B: return 3;
    }
    return 0;
}
int go1(int event)
{
    printf("%c", event);
    switch (event) {
        case A: return 2;
        case B: return 2;
    }
    return 0;
}
int go2(int event)
{
    printf("%c", event);
    switch (event) {
        case A: return 3;
        case B: return 1;
    }
    return 0;
}
int go3(int event)
{
    printf("%c", event);
    switch (event) {
        case A: return 0;
        case B: return 0;
    }
    return 0;
}

void run(FSM *f, int event)
{
    int new_state;
    new_state = f->s[f->current].trans->x(event);
    //printf("fsm: current: %d -> new %d\n", f->current, new_state);
    f->current = new_state;
}

int main()
{
    FSM fsm;
    fsm.current = 0;
    TRANSITION *t;
    int i;

    t = (TRANSITION *) malloc(sizeof(TRANSITION));
    t->x = go0;
    fsm.s[0].trans = t;

    t = (TRANSITION *) malloc(sizeof(TRANSITION));
    t->x = go1;
    fsm.s[1].trans = t;

    t = (TRANSITION *) malloc(sizeof(TRANSITION));
    t->x = go2;
    fsm.s[2].trans = t;

    t = (TRANSITION *) malloc(sizeof(TRANSITION));
    t->x = go3;
    fsm.s[3].trans = t;

    for (i = 0; i < 16; i++) {
        run(&fsm, A);
        run(&fsm, B);
    }
}

