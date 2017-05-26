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
    struct sockaddr_in fromAddr;
    unsigned short echoServPort;
    unsigned int fromSize;
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
        perror("echo word too long");
        exit(1);
    }

    if (argc == 4) 
        echoServPort = atoi(argv[3]);
    else
        echoServPort = 7;

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)
                &echoServAddr, sizeof(echoServAddr)) != echoStringLen) {
        perror("sendto");
        exit(1);
    }

    /* receive a response */
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
                    (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen) {
        perror("recvfrom");
        exit(1);
    }

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

