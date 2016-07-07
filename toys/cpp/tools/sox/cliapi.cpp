//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <stdlib.h>
//#include <netdb.h>
//#include <iostream>
//#include <string>
#include <vector>
#include "sox_api.h"

using namespace std;

#define HOST "localhost"
#define PORT 5000

int main()
{
    vector<unsigned short> ports = { PORT };
    sox_api *sc = new sox_api(sox_api::CLIENT, sox_api::TCP, sox_api::SYNC, ports, "127.0.0.1");
    sc->connect();
    string msg = "hello";
    sc->send(msg, msg.length());
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
