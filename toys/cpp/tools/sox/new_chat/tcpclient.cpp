#include "stdio.h"  
#include "stdlib.h"  
#include "unistd.h"
#include "sys/types.h"  
#include "sys/socket.h"  
#include <arpa/inet.h>
#include "string.h"  
#include "netinet/in.h"  
#include "netdb.h"
#include <string>
#include <thread>

#include "sox_api2.hpp"

// gcc tcpclient.c -o client -pthread 
// ./client 192.168.0.4 (or 127.0.0.1)
struct chat_t {
    struct sockaddr_in cl_addr;
    void *socket;
};

void * receiveMessage(void * socket) {
    long sockfd;
    int ret;
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

void *sendMessage(void * chat) {
    struct chat_t *ch = (struct chat_t *) chat;
    long sockfd, len;
    int ret;
    char buffer[BUF_SIZE]; 
    len = sizeof(ch->cl_addr);
    sockfd = (unsigned long) ch->socket;
    memset(buffer, 0, BUF_SIZE);  
    while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        ret = ::sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &ch->cl_addr, len);  
        if (ret < 0) {  
            printf("Error sending data!\n");  
            exit(1);
        }
    }   
    return nullptr;
}

#define PORT 4444

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
    TCPSocket cli(addr);
    cli.Connect(PORT);
    memset(cli.buffer, 0, BUF_SIZE);

    printf("Enter your messages one by one and press return key!\n");
    std::thread t1{receiveMessage, (void *) cli.sockfd};

    struct chat_t *ch = (struct chat_t *) malloc(sizeof(struct chat_t));
    ch->socket = (void *) cli.sockfd;
    ch->cl_addr = cli.addr;
    std::thread t2{sendMessage, (void *) ch};
 
    t1.join();
    t2.join();

    return 0;
}

int main(int argc, char**argv)
{
    test(argc, argv);
}
