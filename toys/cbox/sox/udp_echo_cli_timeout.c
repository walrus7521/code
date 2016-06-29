#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define ECHOMAX         255
#define TIMEOUT_SECS    2
#define MAXTRIES        5

int tries = 0;

void DieWithError(char *errMsg)
{
    perror(errMsg);
    exit(1);
}

void CatchAlarm(int ignored)
{
    tries++;
}

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in fromAddr;
    unsigned short echoServPort;
    unsigned int fromSize;
    struct sigaction myAction;
    char *servIP;
    char *echoString;
    char echoBuffer[ECHOMAX+1];
    unsigned int echoStringLen;
    int respStringLen;

    if ((argc < 3) || (argc > 4)) {
        printf("Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoString = argv[2];

    if ((echoStringLen = strlen(echoString)) > ECHOMAX) {
        DieWithError("echo word too long");
    }

    if (argc == 4) 
        echoServPort = atoi(argv[3]);
    else
        echoServPort = 7;

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        DieWithError("socket");
    }

    // set signal handler for alarm
    myAction.sa_handler = CatchAlarm;
    if (sigfillset(&myAction.sa_mask) < 0) { // block everything in handler
        DieWithError("sigfillset() failed");
    }

    if (sigaction(SIGALRM, &myAction, 0) < 0) {
        DieWithError("sigaction() failed for SIGALRM");
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
                &echoServAddr, sizeof(echoServAddr)) != echoStringLen) {
        DieWithError("sendto");
    }

    /* receive a response */
    fromSize = sizeof(fromAddr);
    alarm(TIMEOUT_SECS); // set timer
    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
                    (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen) {

        if (errno == EINTR) { // alarm went off
            if (tries < MAXTRIES) {
                printf("timed out, %d more tries...\n", MAXTRIES-tries);

                if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
                            &echoServAddr, sizeof(echoServAddr)) != echoStringLen) {
                    DieWithError("sendto");
                }
                alarm(TIMEOUT_SECS); // restart timer
            } else {
                DieWithError("No response");
            }
        } else {
            DieWithError("recvfrom() failed");
        }
    }
    // recvfrom got something -- cancel the timeout
    alarm(0);

    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr) {
        fprintf(stderr, "Error: received a packet from unknown source.\n");
        exit(1);
    }

    /* null terminate the received data */
    echoBuffer[respStringLen] = '\0';
    printf("Received: %s\n", echoBuffer);

    close(sock);
    exit(0);

}

