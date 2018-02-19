#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* state machines:
        coke machine
        traffic control
        authentication
        initialization process
        fifo
 */

enum state_codes { READY, CHALLENGE, PROOF, SUCCESS };
enum ret_codes { PASS, FAIL, RETRY };

enum ret_codes ready_handler(void)
{
    printf("ready_handler\n");
    return PASS;
}
enum ret_codes challenge_handler(void)
{
   printf("challenge_handler\n");
   return RETRY; //PASS;
}
enum ret_codes proof_handler(void)
{
    printf("proof_handler\n");
    return FAIL;
}
enum ret_codes success_handler(void)
{
    printf("success_handler\n");
    return PASS;
}

struct transition {
    enum state_codes src_state; // state
    enum ret_codes   ret_code;  // status
    enum state_codes dst_state; // handler index
};

struct transition state_transitions[] = {
    /* state, status, handler */
    {READY,     PASS,  CHALLENGE},
    {READY,     FAIL,  READY},
    {READY,     RETRY, READY},
    {CHALLENGE, PASS,  PROOF},
    {CHALLENGE, FAIL,  READY},
    {CHALLENGE, RETRY, CHALLENGE},
    {PROOF,     PASS,  SUCCESS},
    {PROOF,     FAIL,  CHALLENGE},
    {PROOF,     RETRY, PROOF},
    {SUCCESS,   PASS,  SUCCESS},
};

typedef enum ret_codes (*event_handler)(void);
event_handler state[] = {ready_handler, challenge_handler, proof_handler, success_handler};

static enum state_codes lookup_transition(enum state_codes current, enum ret_codes ret) {
    int i = 0;
    enum state_codes temp = SUCCESS;
    for (i = 0;;++i) {
        // find match of state and status
        if (state_transitions[i].src_state == current &&
            state_transitions[i].ret_code  == ret) {
            temp = state_transitions[i].dst_state;
            break;
        }
    }
    return temp;
}

int main(void) {
    enum state_codes curr_state = READY;
    enum ret_codes rc;
    event_handler state_fun;
    while (1) {
        state_fun = state[curr_state];
        rc = state_fun();
        sleep(2);
        if (SUCCESS == curr_state) break;
        curr_state = lookup_transition(curr_state, rc);
    }
    return 0;
}

