#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// http://www.binarytides.com/packet-sniffer-code-c-linux/

void hexdump(const char *buffer, unsigned int length)
{
    char OffsetBuf[10];
    unsigned int LastStart = 0, i, k, j;
    for (i = 0 ; i < length ; i++) {
        if (i % 16 == 0) {
            sprintf(OffsetBuf, "%03x", i);
            printf("%4s:", OffsetBuf);
        }
        if (i % 4 == 0) {
            printf(" ");
        }
        printf("%02x ", buffer[i]);
        if (i % 16 == 15 || i == length-1) {
            if (i == length-1) {
                for (k = i % 16 ; k < 15 ; k++) {
                     printf( "   " );
                     if (k % 4 == 3 && k % 16 != 0) {
                         printf(" ");
                     }
                }
            }
            printf("|");
            for (j = LastStart ; j <= i ; j++) {
                if (j % 4 == 0) {
                    printf(" ");
                }
                if (buffer[j] > 31 && buffer[j] < 127) {
                    printf("%c", buffer[j]);
                } else {
                    printf(".");
                }
            }
            if (i == length-1) {
                printf("\n");
                break;
            }
            printf("\n");
            LastStart += 16;
        }        
    }
}


int main(void) {
    int i, recv_length, sockfd;
    struct sockaddr saddr;
    int saddr_size = sizeof(saddr);
    u_char buffer[65536];
    //sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    //sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);    
    //sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1) {
        printf("fatal: in socket\n");
        return -1;
    }
    while (1) {
        //recv_length = recv(sockfd, buffer, 8000, 0);
        recv_length = recvfrom(sockfd , buffer , 65536 , 0 , &saddr , &saddr_size);
        if (recv_length > 0) {
            printf("Got a %d byte packet\n", recv_length);
            //hexdump(buffer, recv_length);
        }
    }
    return 0;
}
