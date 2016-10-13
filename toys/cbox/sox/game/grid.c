//#include "sox_api2.h"

#include "stdio.h"  
#include "stdlib.h"  
#include "sys/types.h"  
#include "sys/socket.h"  
#include "string.h"  
#include "netinet/in.h"  
#include <arpa/inet.h>
#include "netdb.h"
#include <unistd.h>
#include "pthread.h"


#define ROWS    (30)
#define COLS    (40)
#define VSPACE   (4)
#define HSPACE   (2)

char points[ROWS][COLS];
char ships[ROWS][COLS];

int draw_grid()
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        if (r % HSPACE == 0) {
            for (c = 0; c < COLS; c++) {
                printf("-");
            }
        } else {
            for (c = 0; c < COLS; c++) {
                if (points[r][c]) {
                    printf("%c", points[r][c]);
                }
                else if (c % VSPACE == 1) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int place_ships()
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            points[r][c] = ships[r][c];
        }
    }
    return 0;
}

int boom()
{
    printf("%c", 0x7);
    return 0;
}

#define PORT 4444 
#define BUF_SIZE 2000 

struct chat_t {
    struct sockaddr_in cl_addr;
    void *socket;
};

void * sendMessage(void * chat) {
    struct chat_t *ch = (struct chat_t *) chat;
    long sockfd;
    int ret, len;
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
}

void init(char *ip)
{
    struct sockaddr_in addr, cl_addr;  
    long sockfd;  
    int ret;
    char buffer[BUF_SIZE]; 
    char * serverAddr;
    pthread_t rThread, sThread;
    serverAddr = ip;
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
}

int main()
{
    init("127.0.0.1");
    ships[3][3] = '#';
    ships[3][7] = '#';
    ships[3][11] = '#';
    place_ships();
    points[5][3] = 'o';
    points[5][7] = 'x';
    draw_grid();
    boom();
    return 0;
}
