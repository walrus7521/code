#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <openssl/engine.h>

ENGINE *start_engine(char *engine_type)
{
    ENGINE *e;
    if (!(e = ENGINE_by_id(engine_type))) {
        fprintf(stderr, "Error finding %s ENGINE\n", engine_type);
    } else if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
        fprintf(stderr, "Error using ENGINE\n");
    } else {
        fprintf(stderr, "Error successfully enabled\n");
    }
    return e;
}

int main()
{
    char eng[] = "openssl";
    ENGINE *engine = start_engine(eng);
    if (NULL == engine) {
        printf("%s not started\n", eng);
    } else {
        printf("%s started\n", eng);
    }
}

