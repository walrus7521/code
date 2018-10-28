#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include <arpa/inet.h>
#include <unistd.h>
#include"netdb.h"
#include"pthread.h"

// gcc tcpclient.c -o client -pthread 
// ./client 192.168.0.4 (or 127.0.0.1)

#define PORT 4444 
#define BUF_SIZE 2000 

struct chat_t {
    struct sockaddr_in cl_addr;
    void *socket;
};

void * sendMessage(void * chat) {
    struct chat_t *ch = (struct chat_t *) chat;
    int sockfd, ret, len;
    char buffer[BUF_SIZE]; 
    len = sizeof(ch->cl_addr);
    sockfd = (int) ch->socket;
    memset(buffer, 0, BUF_SIZE);  
    while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &ch->cl_addr, len);  
        if (ret < 0) {  
            printf("Error sending data!\n");  
            exit(1);
        }
    }   
    return NULL;
}

void * receiveMessage(void * socket) {
    long sockfd;
    int ret;
    char buffer[BUF_SIZE]; 
    sockfd = (unsigned long) socket;
    memset(buffer, 0, BUF_SIZE);  
    for (;;) {
        ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
        if (ret < 0) {  
            printf("Error receiving data!\n");    
        } else {
            printf("server: ");
            fputs(buffer, stdout);
            //printf("\n");
        }  
    }
    return NULL;
}

int main(int argc, char**argv) {  
    struct sockaddr_in addr, cl_addr;  
    long sockfd;  
    int ret;
    char buffer[BUF_SIZE]; 
    char * serverAddr;
    pthread_t rThread, sThread;
    if (argc < 2) {
        printf("usage: client < ip address >\n");
        exit(1);  
    }
    serverAddr = argv[1]; 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {  
        printf("Error creating socket!\n");  
        exit(1);  
    }  
    printf("Socket created...\n");   
    memset(&addr, 0, sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = inet_addr(serverAddr);
    addr.sin_port = PORT;     
    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
    if (ret < 0) {  
        printf("Error connecting to the server!\n");  
        exit(1);  
    }  
    printf("Connected to the server...\n");  
    memset(buffer, 0, BUF_SIZE);
    printf("Enter your messages one by one and press return key!\n");
    //creating a new thread for receiving messages from the server
    ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sockfd);
    if (ret) {
        printf("ERROR: Return Code from pthread_create() is %d\n", ret);
        exit(1);
    }
    //while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
    //    ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  
    //    if (ret < 0) {  
    //        printf("Error sending data!\n\t-%s", buffer);  
    //    }
    //}
    struct chat_t *ch = (struct chat_t *) malloc(sizeof(struct chat_t));
    ch->socket = (void *) sockfd;
    ch->cl_addr = addr;
    //creating a new thread for sending messages to the client
    ret = pthread_create(&sThread, NULL, sendMessage, (void *) ch);
    if (ret) {
        printf("ERROR: Return Code from pthread_create() is %d\n", ret);
        exit(1);
    }
    
    pthread_join(rThread, NULL);
    pthread_join(sThread, NULL);
    
    close(sockfd);
    pthread_exit(NULL);
    return 0;    
}  

