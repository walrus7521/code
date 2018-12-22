#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, "tcp://*:5556");
    assert(rc == 0);
    rc = zmq_bind(publisher, "ipc://weather.ipc");
    assert(rc == 0);

    // init random number generator
    srandom((unsigned) time(NULL));
    while (1) {

        // get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode = randof(100000);
        temperature = randof(215) - 80;
        relhumidity = randof(50) + 10;

        // send message to all subscribers
        printf("dude\n");
        char update[20];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}


