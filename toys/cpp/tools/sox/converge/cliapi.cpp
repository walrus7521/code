#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include "sox_api.h"

using namespace std;

#define HOST "localhost"
#define PORT 5000

int main()
{
    sox_api *sc = new sox_api(sox_api::CLIENT, sox_api::TCP, PORT, "127.0.0.1");
    //sox_api(int type, int proto, unsigned short port, const std::string ip):trans_type(type), protocol(proto) {

     
    sc->connect();
    string msg = "hello";
    sc->setbuf(msg, msg.length());
    sc->send();
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
