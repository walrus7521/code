#include <stdio.h>

// https://stackoverflow.com/questions/1371460/state-machines-tutorials

#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)

int entry_state(void){return 0;}
int  idle_state(void){return 0;}
int   bar_state(void){return 0;}
int  exit_state(void){return 0;}

/* array and enum below must be in sync! */
int (* state[])(void) = { entry_state, idle_state, bar_state, exit_state};
enum state_codes { entry, idle, bar, end};

enum ret_codes { ok, fail, repeat};
struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};
/* transitions from end state aren't needed */
struct transition state_transitions[] = {
    {entry, ok,     idle},
    {entry, fail,   end},
    {idle,   ok,     bar},
    {idle,   fail,   end},
    {idle,   repeat, idle},
    {bar,   ok,     end},
    {bar,   fail,   end},
    {bar,   repeat, idle}};

#define EXIT_STATE end
#define ENTRY_STATE entry

enum state_codes lookup_transitions(enum state_codes code, enum ret_codes rc)
{
    return end;
}

int main(int argc, char *argv[]) {
    enum state_codes cur_state = ENTRY_STATE;
    enum ret_codes rc;
    int (* state_fun)(void);

    for (;;) {
        state_fun = state[cur_state];
        rc = state_fun();
        if (EXIT_STATE == cur_state)
            break;
        cur_state = lookup_transitions(cur_state, rc);
    }

    return EXIT_SUCCESS;
}
