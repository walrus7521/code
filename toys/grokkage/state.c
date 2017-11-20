#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

/* state machines:
        coke machine
        traffic control
        authentication
        initialization process
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

