#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int readline(int fd, char *buf, int nbytes) {
    int numread = 0;
    int returnval;

    while (numread < nbytes - 1) {
        returnval = read(fd, buf + numread, 1);
        if (returnval == -1 && errno == EINTR) continue;
        printf("read %d errno %d\n", returnval, errno);
        numread++;
    }
    //errno = EINVAL;
    return numread;
}

int main()
{
    char buf[256];
    int fd = open("test.txt", O_RDWR);
    if(fd < 0)
        return 1;

    printf("hello, world.\n");

    readline(fd, buf, 16);
    printf("buf: %s\n", buf);
  
    close(fd); 
   
}
