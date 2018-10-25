#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

// https://vichargrave.github.io/articles/2013-02/tcp-ip-network-programming-design-patterns-in-cpp
//
using namespace std
 
class TCPStream
{
    int     m_sd;
    string  m_peerIP;
    int     m_peerPort;
 
  public:
    friend class TCPAcceptor;
    friend class TCPConnector;
 
    ~TCPStream()
    {
        close(m_sd);
    } 
    ssize_t send(char* buffer, size_t len);
    ssize_t receive(char* buffer, size_t len);
 
    string getPeerIP();
    int getPeerPort();
 
  private:

    TCPStream(int sd, struct sockaddr_in* address) : msd(sd) {
        char ip[50];
        inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), 
                  ip, sizeof(ip)-1);
        m_peerIP = ip;
        m_peerPort = ntohs(address->sin_port);
    }
    
    TCPStream() {}
    TCPStream(const TCPStream& stream) {}
    
};

 
class TCPConnector
{
  public:
    TCPStream* connect(int port, const char* server);
 
  private:
    int resolveHost(const char* host, struct in_addr* addr);
};
