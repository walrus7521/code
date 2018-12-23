/*
    Copyright 2016 Garrett D'Amore <garrett@damore.org>
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
    "nanomsg" is a trademark of Martin Sustrik
*/

/*  This program serves as an example for how to write a simple PUB SUB
    service, The server is just a single threaded for loop which broadcasts
    messages to clients, every so often.  The message is a binary format
    message, containing two 32-bit unsigned integers.  The first is UNIX time,
    and the second is the number of directly connected subscribers.
    The clients stay connected and print a message with this information
    along with their process ID to standard output.
    To run this program, start the server as pubsub_demo <url> -s
    Then connect to it with the client as pubsub_demo <url>
    For example:
    % ./pubsub_demo tcp://127.0.0.1:5555 -s &
    % ./pubsub_demo tcp://127.0.0.1:5555 &
    % ./pubsub_demo tcp://127.0.0.1:5555 &
    11:23:54 <pid 1254> There are 2 clients connected.
    11:24:04 <pid 1255> There are 2 clients connected.
    ..
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

#define SERVER "server"
#define CLIENT "client"

void
fatal(const char *func)
{
        fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
}

char *
date(void)
{
        time_t now = time(&now);
        struct tm *info = localtime(&now);
        char *text = asctime(info);
        text[strlen(text)-1] = '\0'; // remove '\n'
        return (text);
}

int
server(const char *url)
{
        int sock;

        if ((sock = nn_socket(AF_SP, NN_PUB)) < 0) {
                fatal("nn_socket");
        }
          if (nn_bind(sock, url) < 0) {
                fatal("nn_bind");
        }
        for (;;) {
                char *d = date();
                int sz_d = strlen(d) + 1; // '\0' too
                printf("SERVER: PUBLISHING DATE %s\n", d);
                int bytes = nn_send(sock, d, sz_d, 0);
                if (bytes < 0) {
                        fatal("nn_send");
                }
                sleep(1);
        }
}

int
client(const char *url, const char *name)
{
        int sock;

        if ((sock = nn_socket(AF_SP, NN_SUB)) < 0) {
                fatal("nn_socket");
        }

        // subscribe to everything ("" means all topics)
        if (nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) {
                fatal("nn_setsockopt");
        }
        if (nn_connect(sock, url) < 0) {
                fatal("nn_connet");
        }
        for (;;) {
                char *buf = NULL;
                int bytes = nn_recv(sock, &buf, NN_MSG, 0);
                if (bytes < 0) {
                        fatal("nn_recv");
                }
                printf("CLIENT (%s): RECEIVED %s\n", name, buf); 
                nn_freemsg(buf);
        }
}

int
main(const int argc, const char **argv)
{
        if ((argc >= 2) && (strcmp(SERVER, argv[1]) == 0))
                return (server(argv[2]));

          if ((argc >= 3) && (strcmp(CLIENT, argv[1]) == 0))
                return (client (argv[2], argv[3]));

        fprintf(stderr, "Usage: pubsub %s|%s <URL> <ARG> ...\n",
            SERVER, CLIENT);
        return 1;
}

