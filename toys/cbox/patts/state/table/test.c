#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "watch.h"

int main()
{
    DigitalStopWatchPtr watch =  createWatch();
    startWatch(watch);
    stopWatch(watch);
    destroyWatch(watch);
    return 0;
}
