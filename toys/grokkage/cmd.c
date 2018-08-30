#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* state machines:
        command list
 */

enum state_codes { READY, START, COMPLETE, SUCCESS };
enum ret_codes { PASS, FAIL, RETRY };

enum ret_codes ready_handler(void)
{
    printf("ready_handler\n");
    return PASS;
}
enum ret_codes start_handler(void)
{
   printf("start_handler\n");
   return PASS;
}
enum ret_codes complete_handler(void)
{
    printf("complete_handler\n");
    return PASS;
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
    {READY,     PASS,  START},
    {READY,     FAIL,  READY},
    {READY,     RETRY, READY},
    {START,     PASS,  COMPLETE},
    {START,     FAIL,  READY},
    {START,     RETRY, START},
    {COMPLETE,  PASS,  SUCCESS},
    {COMPLETE,  FAIL,  START},
    {COMPLETE,  RETRY, COMPLETE},
    {SUCCESS,   PASS,  READY},
};

typedef enum ret_codes (*event_handler)(void);
event_handler state[] = {ready_handler, start_handler, complete_handler, success_handler};

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

int reset()
{
    return READY;
}

int main(void) {
    enum state_codes curr_state = READY;
    enum ret_codes rc;
    event_handler state_fun;
    while (1) {
        state_fun = state[curr_state];
        rc = state_fun();
        sleep(2);
        //if (SUCCESS == curr_state) curr_state = reset(); //break;
        curr_state = lookup_transition(curr_state, rc);
    }
}

