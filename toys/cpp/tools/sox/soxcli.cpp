#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>


#include <iostream>
#include <string>
#include <sstream>
#include "sox_client.h"


using namespace std;

#define HOST "coding.debuntu.org"
#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"

char *get_ip(char *host)
{
  struct hostent *hent;
  int iplen = 15; //XXX.XXX.XXX.XXX
  char *ip = (char *)malloc(iplen+1);
  memset(ip, 0, iplen+1);
  if((hent = gethostbyname(host)) == NULL)
  {
    herror("Can't get IP");
    exit(1);
  }
  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
  {
    perror("Can't resolve host");
    exit(1);
  }
  return ip;
}

int main()
{

    char *ip = get_ip((char *) HOST);
    sox_client *sc = new sox_client(sox_client::TCP, 80, ip);
    sc->connect();

    const string host = HOST;
    const string page = PAGE;
    const string getpage = "";
    const string useragent = USERAGENT;
    const string tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

    char query[256];
    memset(query, 0, 256);
    sprintf(query, tpl.c_str(), getpage.c_str(), host.c_str(), useragent.c_str());

    string get(query);
 
    sc->setbuf(get, get.length());
    sc->send();
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
