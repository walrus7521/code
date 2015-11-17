#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct hostent *host;
    int err, i, sock, start, end;
    char hostname[100];
    struct sockaddr_in sa;
    printf("enter hostname or IP: ");
    gets(hostname);
    start = 7;
    end = 27;
    strncpy((char *) &sa, "", sizeof(sa));
    sa.sin_family = AF_INET;
    if (isdigit(hostname[0])) {
        sa.sin_addr.s_addr = inet_addr(hostname);
    }
    for (i = start; i <= end; i++) {
        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("\nSocket");
            exit(1);
        }
        err = connect(sock, (struct sockaddr *) &sa, sizeof(sa));
        if (err < 0) {
            printf("%-5d closed\n", i);
            fflush(stdout);
        } else {
            printf("%-5d open\n", i);
        }
        close(sock);

    }
    printf("\n");
    fflush(stdout);
    return 0;
}
