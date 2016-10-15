#include <iostream>
#include <chrono>
#include "sox_api.h"

using namespace std;

void my_handler(int client_sock)
{
    char buffer[RCVBUFSIZE];
    int rcv_msg_sz, chunk_sz;
    std::cout << "oh yeeeeeaah" << std::endl;
    memset(buffer, 0, sizeof(buffer));
    if ((rcv_msg_sz = ::recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0) {
        std::cout << "size: " << rcv_msg_sz << std::endl;
        perror("recv");
        exit(1);
    }
    printf("recv: %s, size %d\n", buffer, rcv_msg_sz);
    while (rcv_msg_sz > 0) {
        chunk_sz = ::send(client_sock, buffer, rcv_msg_sz, 0);
        if (chunk_sz < 0) {
            perror("send");
            exit(1);
        } else {
            printf("sent %d sized chunk\n", chunk_sz);
        }
        rcv_msg_sz -= chunk_sz;
        //if ((rcv_msg_sz = ::recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0) {
        //    die("recv2");
        //}
    }
}

int main()
{
    vector<unsigned short> ports = { 5000/*, 5001*/ };
    sox_api *sa = new sox_api(sox_api::SERVER, sox_api::TCP, sox_api::ASYNC, ports);
    std::chrono::seconds timeout(2);
    sa->set_timeout(timeout);
    sa->add_callback(my_handler);
    sa->listen();
}
