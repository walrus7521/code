#include "sox_api.h"

using namespace std;

#define HOST "localhost"
#define PORT 5000

int main()
{
    vector<unsigned short> ports = { PORT };
    sox_api *sc = new sox_api(sox_api::CLIENT, sox_api::TCP, sox_api::SYNC, ports, "127.0.0.1");

    sc->connect();
    while (1) {
        cout << "$ ";
        string msg; // = "hello";
        cin >> msg;
        sc->send(msg, msg.length());
        //string rmsg = sc->recv();
        //cout << "> " << rmsg << endl;
    }
}
