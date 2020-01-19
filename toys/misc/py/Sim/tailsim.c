#include <stdio.h>
#include <stdlib.h>

#define MAX 0x10

struct dude { int frame; int x; int y; int z; };

int main()
{
    int frame = 0;
    float x, y, z;
    FILE *logfile;
    struct dude d;

    logfile = fopen("dude.log", "wb");
    if (logfile == NULL) { 
        printf("dude you suck\n");
        return -1;
    }

    printf("hello, world\n");
    while (frame < MAX) {
        d.frame = frame;
        d.x = 1;
        d.y = 2;
        d.z = 3;
        printf("%04x %04x %04x %04x\n", frame, x, y, z);
        int sz = fwrite((void *) &d, sizeof(struct dude), sizeof(struct dude), logfile);
        frame++;
    }
    printf("bye\n");
    fclose(logfile);
}

