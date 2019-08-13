#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// https://yakking.branchable.com/posts/state-machines-in-c/


// states code can be in
enum states {
    START,
    LOOP,
    END,
} state;

// events our code accepts
enum events {
    START_LOOPING,
    PRINT_HELLO,
    STOP_LOOPING,
};

#if 0
void step_state(enum events event) {
    switch(state) {
    case START:
        switch(event) {
        case START_LOOPING:
            state = LOOP;
            break;
        default:
            exit(1);
            break;
        }       
        break;
    case LOOP:
        switch(event) {
        case PRINT_HELLO:
            printf("Hello World!\n");
            break;
        case STOP_LOOPING:
            state = END;
            break;
        default:
            exit(1);
            break;
        }
        break;
    case END:
        exit(1);
        break;
    }
}
#endif

typedef enum states (*event_handler)(enum states, enum events);

enum states start_looping(enum states state, enum events event) {
    return LOOP;
}

enum states print_hello(enum states state, enum events event) {
    printf("Hello World!\n");
    return LOOP;
}

enum states stop_looping(enum states state, enum events event) {
    return END;
}

event_handler transitions[STOP_LOOPING+1][END+1] = {
    [START] = { [START_LOOPING] = start_looping, },
    [LOOP] = { [PRINT_HELLO] = print_hello,
               [STOP_LOOPING] = stop_looping, },
};

void step_state(enum events event) {
    event_handler handler = transitions[event][state];
    if (!handler)
        exit(1);
    state = handler(state, event);
}

int main()
{
    step_state(START_LOOPING);
    step_state(PRINT_HELLO);
    step_state(PRINT_HELLO);
    step_state(STOP_LOOPING);
    return 0;
}
