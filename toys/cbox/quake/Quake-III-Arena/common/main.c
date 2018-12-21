#include <stdio.h>
#include "cmdlib.h"
#include "threads.h"
#include "mutex.h"

void dude(int sup)
{
    printf("sup: %d\n", sup);

}

int main()
{
    ThreadSetDefault();
    RunThreadsOn(1, qtrue, dude);
    int w = GetThreadWork();
    printf("work: %d\n", w);
    
}

