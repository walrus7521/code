#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("$ ");
    while ((read = getline(&line, &len, stdin)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s\n", line);
        if (strncmp("quit", line, 4) == 0) break;
        printf("$ ");
    }

    free(line);
    exit(EXIT_SUCCESS);
}
