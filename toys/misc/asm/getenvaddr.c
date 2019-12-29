#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *env[])
{
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    char *addr = getenv(argv[1]);
    if (addr == NULL) {
        printf("env var %s doesn't exist\n", argv[1]);
    } else {
        printf("env var %s is located at: %p\n", argv[1], addr);
    }
    return 0;
}
