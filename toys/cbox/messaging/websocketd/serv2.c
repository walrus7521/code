#include <stdio.h>


int main()
{
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin)) {
        printf("line: %s\n", line);
    }

}
