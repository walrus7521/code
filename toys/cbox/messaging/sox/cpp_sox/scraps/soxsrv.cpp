#include <iostream>
#include "sox_server.h"

using namespace std;

int main()
{
    sox_server *ss = new sox_server(sox_server::TCP, 5000);

    
    ss->listen();
}
