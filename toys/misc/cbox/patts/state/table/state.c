#include <stdio.h>
#include <unistd.h>

enum state_codes { entry, foo, bar, end };
enum ret_codes { pass, fail, repeat };

static int entry_state(void) {
    printf("Entry\n");
    return pass;
}

static int foo_state(void) {
    static int i = 0;
    printf("Foo\n");
    if (i++ == 0) return repeat;
    else return pass;
}

static int bar_state(void) {
    printf("Bar\n");
    return pass;
}

static int end_state(void) {
    printf("End\n");
    return pass;
}

/* array and enum below must be in sync! */
int (*state[])(void) = { entry_state, foo_state, bar_state, end_state};

struct transition {
    enum state_codes src_state; // state
    enum ret_codes   ret_code;  // status
    enum state_codes dst_state; // handler index
};
/* transitions from end state aren't needed */
struct transition state_transitions[] = {
  /* state, status, handler */
    {entry, pass,   foo},
    {entry, fail,   end},
    {foo,   pass,   bar},
    {foo,   fail,   end},
    {foo,   repeat, foo},
    {bar,   pass,   end},
    {bar,   fail,   end},
    {bar,   repeat, foo}};

static enum state_codes lookup_transitions(enum state_codes current, enum ret_codes ret) {
    int i = 0;
    enum state_codes temp = end;
    for (i = 0;; ++i) {
        // find match to state and status
        if (state_transitions[i].src_state == current && state_transitions[i].ret_code == ret) {
            temp = state_transitions[i].dst_state;
            break;
        }
    }
    return temp;
}

int main(int argc, char *argv[])
{
    enum state_codes cur_state = entry;
    enum ret_codes rc;
    int (*state_fun)(void);
    for (;;) {
        state_fun = state[cur_state];
        rc = state_fun();
        sleep(2);
        if (end == cur_state) break;
        cur_state = lookup_transitions(cur_state, rc);
    }
    return 0;
}
