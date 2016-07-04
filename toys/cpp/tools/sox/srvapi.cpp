#include <iostream>
#include "sox_api.h"

using namespace std;

int main()
{
    //sox_server *ss = new sox_server(sox_server::TCP, 5000);
    sox_api *sa = new sox_api(sox_api::SERVER, sox_api::TCP, 5000, "127.0.0.1");
    
    sa->listen();
}
