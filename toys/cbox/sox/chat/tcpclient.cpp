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

// gcc tcpclient.c -o client -pthread 
// ./client 192.168.0.4 (or 127.0.0.1)

#define PORT 4444 
#define BUF_SIZE 2000 

class sox_api
{
public:
    //sox_api(){}
    sox_api(std::string ip) : srv_addr(ip) {
        this->sockfd = ::socket(AF_INET, SOCK_STREAM, 0);  
        if (this->sockfd < 0) {  
            printf("Error creating socket!\n");  
            exit(1);  
        }  
        printf("Socket created...\n");
    }
    ~sox_api(){    
        ::close(this->sockfd);
    }
    int connect() {
        memset(&this->addr, 0, sizeof(this->addr));
        this->addr.sin_family = AF_INET;
        this->addr.sin_addr.s_addr = ::inet_addr(this->srv_addr.c_str());
        this->addr.sin_port = PORT;
        int ret = ::connect(this->sockfd, (struct sockaddr *) &this->addr, sizeof(struct sockaddr_in));
        if (ret < 0) {
            printf("Error connecting to the server!\n");  
            exit(1);  
        }  
        printf("Connected to the server...\n");  
        return ret;
    }
    int bind(){ return 0; }
    int listen(){ return 0; }
    int recv(){ return 0; }
    int send(){ return 0; }
    int accept(){ return 0; }
    char buffer[BUF_SIZE]; 
    unsigned long sockfd;
    pthread_t rThread;
    struct sockaddr_in addr, cl_addr;  
private:
    std::string srv_addr;
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
