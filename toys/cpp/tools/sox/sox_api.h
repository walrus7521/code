#include <iostream>
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <chrono>

#define MAXPENDING 5
#define RCVBUFSIZE 32
#define BUFSIZE 256

class sox_api
{
public:

    enum { TCP, UDP };
    enum { CLIENT, SERVER };
    enum { SYNC, ASYNC };

    explicit sox_api(int type, int proto, int sync, 
            const std::vector<unsigned short>& ports, 
            const std::string ip = "")
        : trans_type(type), protocol(proto), server_ip(ip), 
        nr_ports(ports.size()) {
        running = true;
        is_async = false;
        if (sync == ASYNC) {
            is_async = true;
        }
        unsigned short port;
        max_desc = -1;
        for (port = 0; port < nr_ports; ++port) {
            serv_sock = create_server_socket(ports[port]);
            serv_socks.push_back(serv_sock);
            if (ports[port] > max_desc) {
                max_desc = ports[port];
            }
        }
    }
    ~sox_api(){ ::close(serv_sock); }
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
        int sent = 0;
        int len;
        while (sent < buflen) {
            len = ::send(serv_sock, buffer, buflen, 0);
            if (len < 0) {
                die("send");
            }
            sent += len;
        }
        return 0; 
    }
    std::string recv() {
        int rcvd = 0;
        int len;
        char buf[32];
        memset(buf, 0, 32);
        while (rcvd < buflen) {
            len = ::recv(serv_sock, buf, BUFSIZE - 1, 0);
            if (len <= 0) {
                die("recv");
            }
            rcvd += len;
            buf[len] = '\0';
        }
        std::string msg(buf);
        return msg; 
    }
    void listen() {
        try {
            if (::listen(serv_sock, MAXPENDING) < 0) {
                die("listen");
            }
            while (running) {
                FD_ZERO(&sock_set);
                unsigned short port;
                for (port = 0; port < nr_ports; ++port) {
                    FD_SET(serv_socks[port], &sock_set);
                }
                sel_timeout.tv_sec = 4; // timeout
                sel_timeout.tv_usec = 0;
                if (select(max_desc + 1, &sock_set, NULL, NULL, &sel_timeout) == 0) {
                    std::cout << "no requests for 4 seconds, still alive" << std::endl;
                } else {
                    for (port = 0; port < nr_ports; ++port) {
                        if (FD_ISSET(serv_socks[port], &sock_set)) {
                            clnt_sock = accept_tcp_connection(serv_socks[port]);
                            if (clnt_sock < 0) {
                                die("accept");
                            }
                            if (cb != nullptr) {
                                if (is_async) {
                                    std::thread t{cb, clnt_sock};
                                    t.join();
                                } else {
                                    cb(clnt_sock);
                                }
                            }
                        }
                    }
                }
                ::close(clnt_sock);
            }
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
    void add_callback(std::function<void(int)> callback)
    {
        cb = callback;
    }
    void set_timeout(std::chrono::seconds period) {
        timeout = period;
    }
 private:
    int trans_type;
    int protocol;
    bool is_async;
    bool running;
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    unsigned short server_port;
    int nr_ports;
    fd_set sock_set;
    int max_desc;
    std::vector<int> serv_socks;
    std::string server_ip;
    unsigned int client_len;
    char buffer[BUFSIZE];
    unsigned int buflen;
    unsigned int send_len;
    std::function<void(int)> cb;
    std::chrono::seconds timeout;
    struct timeval sel_timeout;
    int die(const char *msg) {
        perror(msg);
        exit(1);
    }
    int create_server_socket(unsigned short port) {
        int sock;
        //struct sockaddr_in srv_addr;
        if ((sock = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            die("socket");
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        if (trans_type == CLIENT) {
            server_addr.sin_addr.s_addr = ::inet_addr(server_ip.c_str());
        } else {
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        if (trans_type == SERVER) {
            if (bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                die("bind");
            }
        }
        return sock;
    }
    int accept_tcp_connection(int server_socket) {
        int client_socket;
        struct sockaddr_in cli_addr;
        unsigned int cli_len;
        cli_len = sizeof(cli_addr);
        // wait for client to connect
        if ((client_socket = ::accept(server_socket, (struct sockaddr *) &cli_addr, &cli_len)) < 0) {
            die("accept");
        }
        std::cout << "handling client: " << ::inet_ntoa(cli_addr.sin_addr) << std::endl;
        return client_socket;
    }
};

