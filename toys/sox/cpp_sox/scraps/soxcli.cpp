#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include "sox_client.h"

using namespace std;

#define HOST "localhost"
#define PORT 5000

int main()
{
    sox_client *sc = new sox_client(sox_client::TCP, PORT, "127.0.0.1");
    sc->connect();
    string msg = "hello";
    sc->setbuf(msg, msg.length());
    sc->send();
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
