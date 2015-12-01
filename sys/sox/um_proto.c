#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IPPROTO_TEST 150
#define MAX_BUFFER 100

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAX_BUFFER+1];
    
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TEST);
    printf("\nconnSock:%d",sockfd);
    
    bzero((void *)&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr =inet_addr("127.0.0.1");
    servaddr.sin_port = htons(5351);
    if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    close(sockfd);
}

