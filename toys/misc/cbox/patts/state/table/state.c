#include <stdio.h>
#include <unistd.h>

// https://stackoverflow.com/questions/1371460/state-machines-tutorials

enum state_codes { entry, foo, bar, end};
enum ret_codes { ok, fail, repeat};

static int entry_state(void) 
{
    printf("Entry\n");
    sleep(2);
    return ok;
}

static int foo_state(void)
{
    static int i = 0;
    printf("Foo\n");
    sleep(2);
    if (i++ == 0) return repeat;
    else return ok;
}

static int bar_state(void)
{
    printf("Bar\n");
    sleep(2);
    return ok;
}

static int exit_state(void)
{
    printf("Exit\n");
    sleep(2);
    return ok;
}

/* array and enum below must be in sync! */
int (*state[])(void) = { entry_state, foo_state, bar_state, exit_state};

struct transition {
    enum state_codes src_state;
    enum ret_codes   ret_code;
    enum state_codes dst_state;
};
/* transitions from end state aren't needed */
struct transition state_transitions[] = {
    {entry, ok,     foo},
    {entry, fail,   end},
    {foo,   ok,     bar},
    {foo,   fail,   end},
    {foo,   repeat, foo},
    {bar,   ok,     end},
    {bar,   fail,   end},
    {bar,   repeat, foo}};

static enum state_codes lookup_transitions(enum state_codes current, enum ret_codes ret)
{
    int i = 0;
    enum state_codes temp = end;
    for (i = 0;; ++i) {
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
        if (end == cur_state)
            break;
        cur_state = lookup_transitions(cur_state, rc);
    }

    return 0;
}
