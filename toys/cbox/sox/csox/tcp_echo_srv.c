#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];
    int recvMsgSize;

    memset(echoBuffer, 0, sizeof(echoBuffer));
 
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
        perror("recv");
        exit(1);
    }

    while (recvMsgSize > 0) {
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize) {
            perror("send");
            exit(1);
        }

        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
            perror("recv");
            exit(1);
        }

        printf("echo: %s\n", echoBuffer);

    }

    close(clntSocket);
}

int main(int argc, char *argv[])
{
    int servSock;
    int clntSock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned short echoServPort;
    unsigned int clntLen;

    if (argc != 2) {
        printf("Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(servSock, MAXPENDING) < 0) {
        perror("listen");
        exit(1);
    }

    for (;;) {
        clntLen = sizeof(echoClntAddr);
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0) {
            perror("accept");
            exit(1);
        }

        //printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
        HandleTCPClient(clntSock);
    }

}

