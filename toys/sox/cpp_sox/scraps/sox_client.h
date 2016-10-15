#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFSIZE 256

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
    int setbuf(const std::string& buf, unsigned int len)
    {
        memcpy (buffer, buf.c_str(), len);
        buflen = len;
        return buflen;
    }
    int send() { 
        // BUGBUG needs to be a while loop -- see htmlget, line 68
        if (::send(sock, buffer, buflen, 0) != buflen) {
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
            bytes_rcvd = ::recv(sock, buf, BUFSIZE - 1, 0);
            if (bytes_rcvd <= 0) {
                die("recv");
            }
            total_bytes_rcvd += bytes_rcvd;
            buf[bytes_rcvd] = '\0';
        }
        std::string msg(buf);
        return msg; 
    }

private:
    int type;
    int sock;
    struct sockaddr_in server_addr;
    unsigned short server_port;
    std::string server_ip;
    char *echoString;
    char buffer[BUFSIZE];
    unsigned int buflen;
    unsigned int send_len;
    int bytes_rcvd, total_bytes_rcvd;
    int die(const char *msg) {
        std::cout << "death: ";
        perror(msg);
        exit(1);
    }
};

