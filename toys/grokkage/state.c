#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// https://yakking.branchable.com/posts/state-machines-in-c/

enum states {
    START,
    LOOP,
    END,
}; //state;

enum events {
    START_LOOPING,
    PRINT_ACK,
    STOP_LOOPING,
};

typedef enum states (*event_handler)(enum states, enum events);

enum states start_looping(enum states state, enum events event) {
    assert(state == START && event == START_LOOPING);
    printf("START_LOOPING\n");
    return LOOP;
}

enum states print_hello(enum states state, enum events event) {
    assert(state == LOOP && event == PRINT_ACK);
    printf("ACK\n");
    return LOOP;
}

enum states stop_looping(enum states state, enum events event) {
    assert(state == LOOP && event == STOP_LOOPING);
    printf("STOP_LOOPING\n");
    return END;
}

enum states end_looping(enum states state, enum events event) {
    assert(state == END && event == STOP_LOOPING);
    printf("END_LOOPING\n");
    exit(1);
    return END;
}

event_handler transitions[STOP_LOOPING+1][END+1] = {
    [START] = { [START_LOOPING] = start_looping, },
    [LOOP]  = { [PRINT_ACK]     = print_hello, [STOP_LOOPING] = stop_looping, },
    [END]   = { [END]           = end_looping, [STOP_LOOPING] = end_looping, },
};

//void step_state(enum events event) {
enum states step_state(enum events event, enum states state) {
    event_handler handler = transitions[event][state];
    if (!handler)
        exit(1);
    state = handler(state, event);
    return state;
}

int main(void) {
    enum states the_state = START;
    the_state = step_state(START_LOOPING, the_state);
    the_state = step_state(PRINT_ACK, the_state);
    the_state = step_state(PRINT_ACK, the_state);
    the_state = step_state(STOP_LOOPING, the_state);
    return 0;
}

