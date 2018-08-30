#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
        if(argc!=3) {
                fprintf(stderr, "Usage: datgen writesz char\n");
                exit(EXIT_FAILURE);
        }

        size_t sz = (size_t) atoi(argv[1]);
        char   c  = (char)   *argv[2];

        char **buf = NULL;
        buf = malloc(sz);

        //fprintf(stdout, "sz: %zu, char %c\n", sz, c);

        if(!buf) {
                fprintf(stderr, "Cannot allocate buffer\n");
                exit(EXIT_FAILURE);
        }

        //memset(buf, '1', sz);
        memset(buf, c, sz);

        while(1) {
                if(write(1,buf,sz)<0)
                        exit(EXIT_FAILURE);
        }
}
