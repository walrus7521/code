#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void InterruptSignalHandler(int signalType)
{
    printf("Interrupt received. exiting\n");
    sleep(3); // seconds
    //exit(1);
}

int main()
{
    struct sigaction handler;

    handler.sa_handler = InterruptSignalHandler;
    if (sigfillset(&handler.sa_mask) < 0) {
        perror("sigfillset");
        exit(1);
    }

    handler.sa_flags = 0;

    if (sigaction(SIGINT, &handler, 0) < 0) {
        perror("sigaction");
        exit(1);
    }

    for (;;) {
        pause();
    }

    exit(0);
}
