#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32

class sox_server
{
public:
    enum { TCP, UDP };
    sox_server(int typ, unsigned short port):type(typ){
        server_port = port;
        if ((serv_sock = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            die("socket");
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons(server_port);
        if (bind(serv_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
            die("bind");
        }
    }
    void listen() {
        try {
            if (::listen(serv_sock, MAXPENDING) < 0) {
                die("listen");
            }
            while (1) {
                client_len = sizeof(client_addr);
                if ((clnt_sock = ::accept(serv_sock, (struct sockaddr *) &client_addr, &client_len)) < 0) {
                    die("accept");
                }
                tcp_client_handler(clnt_sock);
            }
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
    ~sox_server(){ ::close(serv_sock); }
 private:
    int type;
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned short server_port;
    unsigned int client_len;
    int die(const char *msg) {
        perror(msg);
        exit(1);
    }
    void tcp_client_handler(int client_sock)
    {
        char buffer[RCVBUFSIZE];
        int rcv_msg_sz, chunk_sz;
        memset(buffer, 0, sizeof(buffer));
        if ((rcv_msg_sz = ::recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0) {
            std::cout << "size: " << rcv_msg_sz << std::endl;
            die("recv1");
        }
        printf("recv: %s, size %d\n", buffer, rcv_msg_sz);
        while (rcv_msg_sz > 0) {
            chunk_sz = ::send(client_sock, buffer, rcv_msg_sz, 0);
            if (chunk_sz < 0) {
                die("send");
            } else {
                printf("sent %d sized chunk\n", chunk_sz);
            }
            rcv_msg_sz -= chunk_sz;
            //if ((rcv_msg_sz = ::recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0) {
            //    die("recv2");
            //}
        }
        ::close(client_sock);
    }
};

