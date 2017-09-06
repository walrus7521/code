#include <iostream>

using namespace std;

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"

int main()
{
    bus_init();
    ios_init();
    dev_init();
    ios_rescan();

    while (1) ;    
}


