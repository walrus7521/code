#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int z;
    int s[2] = {-1, -1};
    z = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    if (z == -1) {
        fprintf(stderr,
                "%s: socketpair(AF_LOCAL, SOCK_STREAM, 0, s)\n",
                strerror(errno));
        return 1;
    }
    /* report the socket file descriptor
     */
    printf("s[0]: %d\n", s[0]);
    printf("s[1]: %d\n", s[1]);

    //system("netstat --unix -p");
    //system("netstat -i -p TCP");
    system("lsof -i tcp");

    return 0;
}
