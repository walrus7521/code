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
#include <string>

#include "sox_api.hpp"

// gcc tcpclient.c -o client -pthread 
// ./client 192.168.0.4 (or 127.0.0.1)


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

using namespace std;

int test(int argc, char**argv)
{
    int ret;
    string addr;
    if (argc < 2) {
        printf("usage: client < ip address >\n");
        exit(1);  
    }
    addr = argv[1];
    sox_api cli(addr);
    cli.connect();
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
    pthread_exit(NULL);
}

int main(int argc, char**argv)
{
    test(argc, argv);
}
