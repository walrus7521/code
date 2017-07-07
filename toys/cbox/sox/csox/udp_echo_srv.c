#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    unsigned short echoServPort;
    int recvMsgSize;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        perror("bind");
        exit(1);
    }

    for (;;) {
        cliAddrLen = sizeof(echoClntAddr);

        /* block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
                        (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0) {
            perror("recvfrom");
            exit(1);
        }

        printf("Handling client %s, msg %s\n", inet_ntoa(echoClntAddr.sin_addr), echoBuffer);

        /* send datagram back to the client */
        if (sendto(sock, echoBuffer, recvMsgSize, 0,
                    (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize) {
            perror("sendto");
            exit(1);
        }

    }

}

