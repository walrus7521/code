#include <iostream>
#include <string>
#include "sox_client.h"


using namespace std;

int main()
{
    sox_client *sc = new sox_client(sox_client::TCP, 5000, "127.0.0.1");
    sc->connect();
    string msg = "hello";


#if 0
    host = "ip address"
    page = "/" by default
char *build_get_query(char *host, char *page)
{
  char *query;
  char *getpage = page;
  const char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

  if(getpage[0] == '/'){
    getpage = getpage + 1;
    fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
  }
  // -5 is to consider the %s %s %s in tpl and the ending \0
  query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
  sprintf(query, tpl, getpage, host, USERAGENT);
  return query;
}
#endif

// use string builder


    sc->setbuf(msg, msg.length());
    sc->send();
    string rmsg = sc->recv();
    cout << "recv: " << rmsg << endl;
}
