#include <stdio.h>
#include <stdint.h>

struct timer_list
{
    struct timer_list *next, *prev;
    uint32_t expires;
    uint32_t data;
    void (*callback)(uint32_t, uint32_t);
};

void timer_handler(uint32_t exp, uint32_t data)
{
}

void init_timer(struct timer_list *tlist)
{
}

void add_timer(struct timer_list *tlist)
{
}

int main()
{
    struct timer_list test_timer;
    uint32_t time;
    uint32_t data;

    
}

