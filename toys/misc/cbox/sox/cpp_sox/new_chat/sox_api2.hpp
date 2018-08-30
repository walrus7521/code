#ifndef _SOX_API_H_
#define _SOX_API_H_

#include <memory>

#define BUF_SIZE 2000
#define CLADDR_LEN 100

typedef long SOCKET;

class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort)
    {
        GetAsSockAddrIn()->sin_family = AF_INET;
        GetAsSockAddrIn()->sin_addr.s_addr = htonl(inAddress);
        GetAsSockAddrIn()->sin_port = htons(inPort);
    }
    SocketAddress(const sockaddr& inSockAddr)
    {
        memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
    }
    size_t GetSize() const { return sizeof(sockaddr); }
private:
    sockaddr mSockAddr;
    sockaddr_in *GetAsSockAddrIn()
    { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
};
typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

class UDPSocket
{
};

class TCPSocket
{
public:
    TCPSocket(){
        this->sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd < 0) {
            printf("Error creating socket!\n");
            exit(1);
        }
        printf("Socket created...\n");    
    }
    TCPSocket(std::string ip) : srv_addr(ip) {
        this->sockfd = ::socket(AF_INET, SOCK_STREAM, 0);  
        if (this->sockfd < 0) {  
            printf("Error creating socket!\n");  
            exit(1);  
        }  
        printf("Socket created...\n");
    }
    ~TCPSocket(){    
        ::close(this->sockfd);
    }
    int Connect(int port) {
        memset(&this->addr, 0, sizeof(struct sockaddr_in));
        this->addr.sin_family = AF_INET;
        this->addr.sin_addr.s_addr = ::inet_addr(this->srv_addr.c_str());
        this->addr.sin_port = port;
        int ret = ::connect(this->sockfd, (struct sockaddr *) &this->addr, sizeof(struct sockaddr_in));
        if (ret < 0) {
            printf("Error connecting to the server!\n");  
            exit(1);  
        }  
        printf("Connected to the server...\n");  
        return ret;
    }
    int Bind(int port) { 
        memset(&this->addr, 0, sizeof(struct sockaddr_in));
        this->addr.sin_family = AF_INET;
        this->addr.sin_addr.s_addr = INADDR_ANY;
        this->addr.sin_port = port; 
        int ret = ::bind(this->sockfd, (struct sockaddr *) &this->addr, sizeof(struct sockaddr_in));
        if (ret < 0) {
            printf("Error binding!\n");
            exit(1);
        }
        printf("Binding done...\n");
        return 0;
    }
    int Listen(){ 
        ::listen(sockfd, 5);
        return 0; 
    }
    int Accept(){ 
        char clientAddr[CLADDR_LEN];
        socklen_t len = sizeof(struct sockaddr_in);
        long newsockfd = ::accept(sockfd, (struct sockaddr *) &cl_addr, &len);
        if (newsockfd < 0) {
            printf("Error accepting connection!\n");
            exit(1);
        } 
        inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
        printf("Connection accepted from %s...\n", clientAddr); 
        return newsockfd; 
    }
    int Recv(){ return 0; }
    int Send(){ return 0; }

//private:
    char buffer[BUF_SIZE]; 
    SOCKET sockfd;
    struct sockaddr_in addr, cl_addr;  
    std::string srv_addr;
};

#endif

