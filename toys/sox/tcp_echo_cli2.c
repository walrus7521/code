#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RCVBUFSIZE 32

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    unsigned short echoServPort;
    char *servIP;
    char *echoString;
    char echoBuffer[RCVBUFSIZE];
    unsigned int echoStringLen;
    int bytesRcvd, totalBytesRcvd;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int i;
    for (i = 0; i < argc; i++) {
        printf("%d => %s\n", i, argv[i]);
    }


    if ((argc < 3) || (argc > 4)) {
        printf("Usage: %s <Server IP> [<Echo Port>]\n", argv[0]);
        exit(0);
    }

    servIP = argv[1];

    if (argc == 3) 
        echoServPort = atoi(argv[2]);
    else
        echoServPort = 7;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("$ ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s\n", line);
        if (strncmp("quit", line, 4) == 0) break;
        echoString = line;
        echoStringLen = strlen(echoString)-1;

        if (send(sock, echoString, echoStringLen, 0) != echoStringLen) {
            perror("send");
            exit(1);
        }

        totalBytesRcvd = 0;
        printf("Received: ");
        while (totalBytesRcvd < echoStringLen) {
            if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0) {
                perror("recv");
                exit(1);
            }
            totalBytesRcvd += bytesRcvd;
            echoBuffer[bytesRcvd] = '\0';
            printf("%s", echoBuffer);
        }

        printf("$ ");
    }


    printf("\n");
    close(sock);
    exit(0);
    
}

