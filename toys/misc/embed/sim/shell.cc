#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#include "sim.h"
#include "bus.h"
#include "ios.h"
#include "dev.h"
#include "hal.h"
#include "ifs.h"

void shell(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Sim> ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        if (strncmp("quit", line, 4) == 0) break;
        printf("Sim> ");
    }
    free(line);
}

int main()
{
    hal_init();
    bus_init();
    ios_init();
    dev_init();
    ifs_init();
    ios_rescan();

    shell();
    //shell2();
    while (1) ;

}


