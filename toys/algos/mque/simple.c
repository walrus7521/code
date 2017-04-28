#include <stdio.h>
#include "simple.h"


QUEUE_DEFINITION(uart_msg_queue, struct uart_msg, 4);
/*
  The above macro provides implementations of:
   uart_msg_queue_init()
   uart_msg_queue_enqueue()
   uart_msg_queue_dequeue()
*/

void shared_state_init(struct shared_state * const p_state) {
  uart_msg_queue_init(&p_state->uart_msg_queue);
}

int main()
{
    struct shared_state ss;
    shared_state_init(&ss);

    int i;
    for (i = 0; i < 4; i++) {
        struct uart_msg new_msg = {
            .msg = {1,2,3,4,5,1,2,3,4,5,1,2,3,4,5}
        };
        
        uart_msg_queue_enqueue();
    }
}
