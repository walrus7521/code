#include <iostream>
#include <string>
#include <sstream>
#include "sox_client.h"


using namespace std;

#define HOST "coding.debuntu.org"
#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"

void test()
{
    const string host = "127.0.0.1";
    const string page = PAGE;
    const string getpage = "/";
    const string useragent = USERAGENT;
    const string tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

    char query[256];
    sprintf(query, tpl.c_str(), getpage.c_str(), host.c_str(), useragent.c_str());

    string q(query);
    cout << q << endl;

}

int main()
{
    //test();
    //return 0;


    sox_client *sc = new sox_client(sox_client::TCP, 5000, "127.0.0.1");
    sc->connect();

    const string host = "127.0.0.1";
    const string page = PAGE;
    const string getpage = "/";
    const string useragent = USERAGENT;
    const string tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

    char query[256];
    sprintf(query, tpl.c_str(), getpage.c_str(), host.c_str(), useragent.c_str());

    string msg(query);
    //string msg = "hello";
 
    sc->setbuf(msg, msg.length());
    sc->send();
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
