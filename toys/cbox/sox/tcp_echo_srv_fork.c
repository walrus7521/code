#include "tcp_echo_srv.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int servSock;
    int clntSock;
    unsigned short echoServPort;
    pid_t processID;
    unsigned int childProcCount = 0; // number of child processes

    if (argc != 2) {
        printf("Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    // allocates, bind, and marks server socket ready to accept incoming
    servSock = CreateTCPServerSocket(echoServPort);

    for (;;) {

        // blocks until a valid connection is established
        clntSock = AcceptTCPConnection(servSock);
        // fork child proc and report any errors
        if ((processID == fork()) < 0) {
            DieWithError("fork() failed");
        } else
        if (processID == 0) {
            close(servSock);
            HandleTCPClient(clntSock);
            exit(0);
        }

        printf("with child process: %d\n", (int) processID);
        close(clntSock);
        childProcCount++;

        while (childProcCount) { // cleanup all zombies

            processID = waitpid((pid_t) -1, NULL, WNOHANG); // non-blocking wait
            if (processID < 0) { // waitpid error?
                DieWithError("waitpid() failed");
            } else
            if (processID == 0) { // no zombie to wait on
                break;
            } else {
                childProcCount--;
            }
        }
    }
    // not reached

}

