#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>

#define ECHOMAX 255
int sock;

void DieWithError(char *errMsg)
{
    perror(errMsg);
    exit(1);
}

void UseIdleTime()
{
    printf(".\n");
    sleep(3);
}

void SIGIOHandler(int signalType)
{
    struct sockaddr_in echoClntAddr;
    unsigned int clntLen;
    int recvMsgSize;
    char echoBuffer[ECHOMAX];

    do { // as long as there is input

        clntLen = sizeof(echoClntAddr);
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
                    (struct sockaddr *) &echoClntAddr, &clntLen)) < 0) {

            // only acceptable error: recvfrom() would have blocked
            if (errno != EWOULDBLOCK) {
                DieWithError("recvfrom() failed");
            }
        } else {

            printf("Handling client %s => %s\n", inet_ntoa(echoClntAddr.sin_addr), echoBuffer);

            if (sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *)
                        &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize) {
                DieWithError("sendto() failed");
            }
        }

    } while (recvMsgSize >= 0);
    
}

int main(int argc, char *argv[])
{
    struct sockaddr_in echoServAddr;
   unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    unsigned short echoServPort;
    int recvMsgSize;
    struct sigaction handler;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        DieWithError("socket() failed");
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        DieWithError("bind() failed");
    }

    // setup signal handler
    handler.sa_handler = SIGIOHandler;
    // create masks for all signals
    if (sigfillset(&handler.sa_mask) < 0) {
        DieWithError("sigfillset() failed");
    }

    // no flags
    handler.sa_flags = 0;

    if (sigaction(SIGIO, &handler, 0) < 0) {
        DieWithError("sigaction() failed for SIGIO");
    }

    // we must own the socket to receive the SIGIO message
    if (fcntl(sock, F_SETOWN, getpid()) < 0) {
        DieWithError("Unable to set process owner to us");
    }

    // arrange for non-blocking IO and SIGIO delivery
    // O_NONBLOCK is used so that recvfrom call in SIGIOHandler will not block
    if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0) {
        DieWithError("Unable to put client sock into nonblocking/async mode");
    }

    // time to do real work

    for (;;) {
        UseIdleTime();
        
        // NOT REACHED
    }

}

