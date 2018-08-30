/*
 * Perform I/O on a socket pair
 *
 */

#include "pch.h"

int main()
{
    int z;
    int s[2] = {-1, -1};
    char *cp;
    char buf[80];

    z = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);

    if (z == -1) {
        fprintf(stderr,
                "%s: socketpair(AF_LOCAL, SOCK_STREAM, 0, s)\n",
                strerror(errno));
        return 1;
    }

    /* write a message to socket s[1]
     */
    z = write(s[1], cp="Hello?", 6);
    CHK_ERROR(z, "write error");
    printf("wrote msg '%s' on s[1]\n", cp);

    /* read socket */
    z = read(s[0], buf, sizeof(buf));
    CHK_ERROR(z, "read error");
    buf[z] = '\0';
    printf("read msg '%s' on s[0]\n", buf);

    /* send reply */
    z = write(s[0], cp="Go away!", 8);
    CHK_ERROR(z, "reply error");
    printf("wrote reply '%s' on s[0]\n", cp);

    z = read(s[1], buf, sizeof(buf));
    CHK_ERROR(z, "read error");
    buf[z] = '\0';
    printf("read reply '%s' on s[1]\n", buf);

    close(s[0]);
    close(s[1]);

    puts("Done.");

    return 0;
}
