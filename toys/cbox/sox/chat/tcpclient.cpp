#include "stdio.h"  
#include "stdlib.h"  
#include "unistd.h"
#include "sys/types.h"  
#include "sys/socket.h"  
#include <arpa/inet.h>
#include "string.h"  
#include "netinet/in.h"  
#include "netdb.h"
#include "pthread.h"

// gcc tcpclient.c -o client -pthread 
// ./client 192.168.0.4 (or 127.0.0.1)

#define PORT 4444 
#define BUF_SIZE 2000 

class sox_api
{
public:
    sox_api(){}
    ~sox_api(){}
    int bind(){}
    int listen(){}
    int recv(){}
    int send(){}
    int accept(){}
//private:
    unsigned long sockfd;
    struct sockaddr_in addr, cl_addr;  
    char buffer[BUF_SIZE]; 
    char *serverAddr;
    pthread_t rThread;
};

void * receiveMessage(void * socket) {
    unsigned long sockfd, ret;
    char buffer[BUF_SIZE]; 
    sockfd = (unsigned long) socket;
    memset(buffer, 0, BUF_SIZE);  
    for (;;) {
        ret = ::recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
        if (ret < 0) {  
            printf("Error receiving data!\n");    
        } else {
            printf("server: ");
            fputs(buffer, stdout);
            //printf("\n");
        }  
    }
}

int test(int argc, char**argv)
{
    int ret;
    sox_api cli;
    pthread_t rThread;
    if (argc < 2) {
        printf("usage: client < ip address >\n");
        exit(1);  
    }
    cli.serverAddr = argv[1]; 
    cli.sockfd = ::socket(AF_INET, SOCK_STREAM, 0);  
    if (cli.sockfd < 0) {  
        printf("Error creating socket!\n");  
        exit(1);  
    }  
    printf("Socket created...\n");
    memset(&cli.addr, 0, sizeof(cli.addr));
    cli.addr.sin_family = AF_INET;
    cli.addr.sin_addr.s_addr = ::inet_addr(cli.serverAddr);
    cli.addr.sin_port = PORT;
    ret = connect(cli.sockfd, (struct sockaddr *) &cli.addr, sizeof(cli.addr));  
    if (ret < 0) {  
        printf("Error connecting to the server!\n");  
        exit(1);  
    }  
    printf("Connected to the server...\n");  
    memset(cli.buffer, 0, BUF_SIZE);
    printf("Enter your messages one by one and press return key!\n");
    ret = pthread_create(&cli.rThread, NULL, receiveMessage, (void *) cli.sockfd);
    if (ret) {
        printf("ERROR: Return Code from pthread_create() is %d\n", ret);
        exit(1);
    }
    while (fgets(cli.buffer, BUF_SIZE, stdin) != NULL) {
        ret = ::sendto(cli.sockfd, cli.buffer, BUF_SIZE, 0, (struct sockaddr *) &cli.addr, sizeof(cli.addr));  
        if (ret < 0) {  
            printf("Error sending data!\n\t-%s", cli.buffer);  
        }
    }
    ::close(cli.sockfd);
    pthread_exit(NULL);
}

int main(int argc, char**argv)
{
    test(argc, argv);
}
