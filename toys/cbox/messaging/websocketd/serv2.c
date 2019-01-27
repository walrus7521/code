#include <stdio.h>
#include <unistd.h>


int main()
{
    char *line = NULL;
    size_t len = 0;

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    
    while (getline(&line, &len, stdin)) {
        printf("dude: %s\n", line);
        sleep(2);
    }

}
