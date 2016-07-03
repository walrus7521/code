#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define RCVBUFSIZE 32

class sox_client
{
public:
    enum { TCP, UDP };
    sox_client(int typ, unsigned short port, const std::string ip):type(typ){
        server_ip   = ip;
        server_port = port;
        if ((sock = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            die("socket");
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = ::inet_addr(server_ip.c_str());
        server_addr.sin_port = htons(server_port);
    }
    ~sox_client(){ ::close(sock); }
    int connect() {
        int rc;
        rc = ::connect(sock, 
                     (struct sockaddr *) &server_addr, 
                     sizeof(server_addr));
        if (rc < 0) {
            die("connect");
        }
        return rc;
    }
    int send(std::string buf, unsigned int len) { 
        if (::send(sock, buf.c_str(), len, 0) != len) {
            die("send");
        }
        return 0; 
    }
    std::string recv() {
        total_bytes_rcvd = 0;
        char buf[32];
        memset(buf, 0, 32);
        while (total_bytes_rcvd < echoStringLen) {
            if ((bytes_rcvd = ::recv(sock, buf, RCVBUFSIZE - 1, 0)) <= 0) {
                perror("recv");
                exit(1);
            }
            total_bytes_rcvd += bytes_rcvd;
            echoBuffer[bytes_rcvd] = '\0';
        }
        //std::string msg(echoBuffer);
        std::string msg("goodbye");
        return msg; 
    }

private:
    int type;
    int sock;
    struct sockaddr_in server_addr;
    unsigned short server_port;
    std::string server_ip;
    char *echoString;
    char echoBuffer[RCVBUFSIZE];
    unsigned int echoStringLen;
    int bytes_rcvd, total_bytes_rcvd;
    int die(const char *msg) {
        perror(msg);
        exit(1);
    }
};

