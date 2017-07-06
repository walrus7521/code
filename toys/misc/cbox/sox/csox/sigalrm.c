#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

#define TIMEOUT_SECS    2
int tries = 5;

void DieWithError(char *errMsg)
{
    perror(errMsg);
    exit(1);
}

void CatchAlarm(int ignored)
{
    printf("got an alarm\n");
    tries--;
    if (tries) {
        alarm(TIMEOUT_SECS); // set timer
    }
}

int main()
{
    struct sigaction myAction;
    // set signal handler for alarm
    myAction.sa_handler = CatchAlarm;
    if (sigfillset(&myAction.sa_mask) < 0) { // block everything in handler
        DieWithError("sigfillset() failed");
    }
    if (sigaction(SIGALRM, &myAction, 0) < 0) {
        DieWithError("sigaction() failed for SIGALRM");
    }
    alarm(TIMEOUT_SECS); // set timer
    while (tries) sleep(1); 
    printf("and we're done\n");
    alarm(0);
}
