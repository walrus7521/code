#include <stdio.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <CoreFoundation/CoreFoundation.h> // For CFDictionary

// clang -framework Foundation -framework IOKit kevent.c
//
//
//
// In OS X, you can just #include <IOKit/IOKitLib.h>. Not so on iOS
// in which the following need to be included directly

#define IOKIT // to unlock device/device_types..
#include <device/device_types.h> // for io_name, io_string


int main(int argc, char *argv[])
{
    pid_t pid;
    int kq;
    int rc;
    int done;
    struct kevent ke;

    pid = atoi(argv[1]);
    kq = kqueue();

    if (kq == -1) { perror("kqueue"); exit(2); }

    EV_SET(&ke, pid, EVFILT_PROC, EV_ADD,
        NOTE_EXIT | NOTE_FORK | NOTE_EXEC , 0, NULL);
   
    // Register event
    rc = kevent(kq, &ke, 1, NULL, 0, NULL);

    if (rc < 0) { perror ("kevent"); exit (3); }

    done = 0;
    while (!done) {

        memset(&ke, '\0', sizeof(struct kevent));
        
        // This blocks until an event matching the filter occurs
        rc = kevent(kq, NULL, 0, &ke, 1, NULL);
        
        if (rc < 0) { perror ("kevent"); exit (4); }

        if (ke.fflags & NOTE_FORK)
            printf("PID %ld fork()ed\n", ke.ident);
        if (ke.fflags & NOTE_EXEC)
            printf("pid %ld has exec()ed\n", ke.ident);

        if (ke.fflags & NOTE_EXIT) {
            printf("pid %ld has exited\n", ke.ident);
            done++;
        }
    }

}
