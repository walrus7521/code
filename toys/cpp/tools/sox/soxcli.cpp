#include <iostream>
#include <string>
#include "sox_client.h"


using namespace std;

int main()
{
    sox_client *sc = new sox_client(sox_client::TCP, 5000, "127.0.0.1");
    sc->connect();
    string msg = "hello";
    sc->send(msg, msg.length());
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
