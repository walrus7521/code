#ifndef _SOX_API_H_
#define _SOX_API_H_

#define BUF_SIZE 2000
#define CLADDR_LEN 100

class sox_api
{
public:
    sox_api(){
        this->sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd < 0) {
            printf("Error creating socket!\n");
            exit(1);
        }
        printf("Socket created...\n");    
    }
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
    int connect(int port) {
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
    int bind(int port) { 
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
    int listen(){ return 0; }
    int recv(){ return 0; }
    int send(){ return 0; }
    int accept(){ return 0; }
    char buffer[BUF_SIZE]; 
    long sockfd;
    pthread_t rThread;
    struct sockaddr_in addr, cl_addr;  
//private:
    std::string srv_addr;
};

#endif

