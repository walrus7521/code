#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
/* Implements a very simple web page grabber. The program should print the HTML for the index page at any web site. */
int main(int argc, char *argv[])
{
    int i, s; char str[1024];
    char msg[] = "GET  /   HTTP/1.0\r\nHost: www.paris.fr\r\nConnection: close\r\n\r\n";
    struct sockaddr_in si;
    struct hostent *h = gethostbyname("paris.fr");
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&si, 0, sizeof(si));
    memcpy(&si.sin_addr, h->h_addr_list[0], sizeof(struct in_addr));
    si.sin_port = htons(80);
    si.sin_family = AF_INET;
    i = connect(s, (const struct sockaddr *) &si, sizeof(si));
    i = send(s,msg, sizeof(msg), 0);
    i = recv(s, str, sizeof(str), 0);
    if (i > 0) {
        str[i] = 0;  /* ALL C/C++ strings must end with '\0' */
        printf("%s\n", str);
    }
    close(s);
}

