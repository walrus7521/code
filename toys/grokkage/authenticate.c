#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//
// OSI: https://en.wikipedia.org/wiki/OSI_model
// 7. Application Data: High-level APIs, including resource sharing, remote file access
// 6. Presentation: Translation of data between a networking service and an application; including character encoding, data compression and encryption/decryption
// 5. Session:  Managing communication sessions, i.e. continuous exchange of information in the form of multiple back-and-forth transmissions between two nodes
// 4. Transport Segment (TCP) / Datagram (UDP): Reliable transmission of data segments between points on a network, including segmentation, acknowledgement and multiplexing
// 3. Network:  Packet  Structuring and managing a multi-node network, including addressing, routing and traffic control
// 2. Data link Frame:  Reliable transmission of data frames between two nodes connected by a physical layer
// 1. Physical:
//
// presentation: code 
// session: auth
// transport: order,status
// network: msg

// https://yakking.branchable.com/posts/state-machines-in-c/

enum states {
    READY,
    CHALLENGE,
    PROOF,
    SUCCESS,
};

enum events {
    READY_LOOP,
    CHALLENGE_LOOP,
    PROOF_LOOP,
    STOP_LOOP,
};

typedef enum states (*event_handler)(enum states, enum events);

enum states ready_loop(enum states state, enum events event) {
    assert(state == READY); // && event == READY_LOOPING);
    printf("READY\n");
    return CHALLENGE;
}

enum states challenge_loop(enum states state, enum events event) {
    assert(state == CHALLENGE); // && event == CHALLENGE_LOOPING);
    printf("CHALLENGE\n");
    return PROOF;
}

enum states proof_loop(enum states state, enum events event) {
    assert(state == PROOF && event == PROOF_LOOPING);
    printf("PROOF\n");
    return SUCCESS;
}

enum states stop_loop(enum states state, enum events event) {
    assert(state == SUCCESS && event == STOP_LOOPING);
    printf("STOP_LOOPING\n");
    return SUCCESS;
}

event_handler transitions[STOP_LOOPING+1][SUCCESS+1] = {
    [READY]     = { [READY_LOOPING]     = ready_loop,       },
    [CHALLENGE] = { [CHALLENGE_LOOPING] = challenge_loop,   },
    [PROOF]     = { [PROOF_LOOPING]     = proof_loop,       },
    [SUCCESS]   = { [STOP_LOOPING]      = stop_loop, [STOP_LOOPING] = stop_loop, },
};

enum states step_state(enum events event, enum states state) {
    event_handler handler = transitions[event][state];
    if (!handler)
        exit(1);
    state = handler(state, event);
    return state;
}

int main(void) {
    enum states the_state = READY;
    while (1) {
        the_state = step_state(READY_LOOPING, the_state);
        if (the_state == SUCCESS) {
            printf("SUCCESS\n");
            return 0;
        }
    }
    //the_state = step_state(CHALLENGE_LOOPING, the_state);
    //the_state = step_state(PRINT_ACK, the_state);
    //the_state = step_state(STOP_LOOPING, the_state);
    return 0;
}

