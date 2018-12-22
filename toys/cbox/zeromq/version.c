#include "zhelpers.h"

int main()
{
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    printf("0MQ ver: %d.%d.%d\n", major, minor, patch);
}

