#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32
#define BUFSIZE 256

class sox_api
{
public:
    enum { TCP, UDP };
    enum { CLIENT, SERVER };

    sox_api(int type, int proto, unsigned short port, const std::string ip):trans_type(type), protocol(proto) {

        server_ip   = ip; // add to initializer list
        server_port = port;

        if ((serv_sock = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            die("socket");
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);

        if (trans_type == CLIENT) {
            server_addr.sin_addr.s_addr = ::inet_addr(server_ip.c_str());
        } else {
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
         
        if (trans_type == SERVER) {
            if (bind(serv_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                die("bind");
            }
        }

    }
    int connect() {
        int rc;
        rc = ::connect(serv_sock, 
                     (struct sockaddr *) &server_addr, 
                     sizeof(server_addr));
        if (rc < 0) {
            die("connect");
        }
        return rc;
    }
    int setbuf(const std::string& buf, unsigned int len)
    {
        memcpy (buffer, buf.c_str(), len);
        buflen = len;
        return buflen;
    }
    int send() { 
        // BUGBUG needs to be a while loop -- see htmlget, line 68
        if (::send(serv_sock, buffer, buflen, 0) != buflen) {
            die("send");
        }
        //send_len = buflen;
        return 0; 
    }
    std::string recv() {
        total_bytes_rcvd = 0;
        char buf[32];
        memset(buf, 0, 32);
        while (total_bytes_rcvd < buflen) {
            bytes_rcvd = ::recv(serv_sock, buf, BUFSIZE - 1, 0);
            if (bytes_rcvd <= 0) {
                die("recv");
            }
            total_bytes_rcvd += bytes_rcvd;
            buf[bytes_rcvd] = '\0';
        }
        std::string msg(buf);
        return msg; 
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
    ~sox_api(){ ::close(serv_sock); }
 private:
    int trans_type;
    int protocol;
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned short server_port;
    std::string server_ip;
    unsigned int client_len;
    char buffer[BUFSIZE];
    unsigned int buflen;
    unsigned int send_len;
    int bytes_rcvd, total_bytes_rcvd;
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

