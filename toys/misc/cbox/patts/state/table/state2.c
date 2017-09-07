#include <stdio.h>
#include <unistd.h>

// brute force approach
typedef enum {entry, foo, bar, end} state_t;
typedef enum ret_codes { ok, fail, repeat } status_t;

static status_t entry_handler(void) 
{
    printf("Entry\n");
    return ok;
}

static status_t foo_handler(void)
{
    static int i = 0;
    printf("Foo\n");
    if (i++ == 0) return repeat;
    else return ok;
}

static status_t bar_handler(void)
{
    printf("Bar\n");
    return ok;
}

static status_t end_handler(void)
{
    printf("End\n");
    return ok;
}

// one "could" return a pair from each handler {state, status}.
status_t (*handler[])(void) = { entry_handler, foo_handler, bar_handler, end_handler};

void stater()
{
    state_t state = entry;
    status_t status = ok;
    while (1)
    {
        status = handler[state]();
        switch (state)
        {
            case entry:
                //status = entry_handler();
                if (status == ok)
                {
                    printf("0 -> 1\n");
                    state++;
                }
                else if (status == fail)
                {
                    printf("0 -> 0\n");
                }
                break;
            case foo:
                //status = foo_handler();
                if (status == ok) 
                {
                    printf("1 -> 2\n");
                    state++;
                }    
                else if (status == repeat)
                {
                    printf("1 -> 1\n");
                }
                else if (status == fail)
                {
                    printf("1 -> 0\n");
                    state--;
                }
                break;
            case bar:
                //status = bar_handler();
                if (status == ok) 
                {
                    printf("2 -> 3\n");
                    state++;
                }
                else if (status == fail)
                {
                    printf("2 -> 0\n");
                    state -= 2;
                }    
                break;
            case end:
                //status = end_handler();
                printf("3 -> End\n");
                goto exit;
                break;
            default:
                break;
        }
        sleep(1);
    }
exit:
    return;
}

int main()
{
    stater();
}
