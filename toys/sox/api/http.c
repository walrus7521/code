/*
AUTHOR: Abhijeet Rastogi (http://www.google.com/profiles/abhijeet.1989)
This is a very simple HTTP server. Default port is 10000 and ROOT for the server is your current working directory..

You can provide command line arguments like:- $./a.aout -p [port] -r [path]

for ex. 
$./a.out -p 50000 -r /home/
to start a server at port 50000 with root directory as "/home"

$./a.out -r /home/shadyabhi
starts the server at port 10000 with ROOT as /home/shadyabhi

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>

//#include <map>
//#include <vector>
//#include <string>
//#include <iostream>

#define CONNMAX 1000
#define BYTES 1024

char *ROOT;
int listenfd, clients[CONNMAX];
void error(char *);
void startServer(char *);
void respond(int);

int main(int argc, char* argv[])
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    char c;    
    
    //Default Values PATH = ~/ and PORT=10000
    char PORT[6];
    ROOT = getenv("PWD");
    strcpy(PORT,"10000");

    int slot=0;

    printf("starting up the server:: main\n\n");

    //Parsing the command line arguments
    while ((c = getopt (argc, argv, "p:r:")) != -1) {
        switch (c) {
            case 'r':
                ROOT = (char *) malloc(strlen(optarg));
                strcpy(ROOT,optarg);
                break;
            case 'p':
                strcpy(PORT,optarg);
                break;
            case '?':
                fprintf(stderr,"Wrong arguments given!!!\n");
                exit(1);
            default:
                exit(1);
        }
    }
    
    printf("Server started at port no. %s%s%s with root directory as %s%s%s\n","\033[92m",PORT,"\033[0m","\033[92m",ROOT,"\033[0m");
    // Setting all elements to -1: signifies there is no client connected
    int i;
    for (i=0; i<CONNMAX; i++)
        clients[i]=-1;
    startServer(PORT);

    // ACCEPT connections
    while (1) {
        addrlen = sizeof(clientaddr);
        clients[slot] = accept(listenfd, (struct sockaddr *) &clientaddr, &addrlen);
        printf("accepting connection...\n\n");
        if (clients[slot]<0)
            perror ("accept() error");
        else {
            if ( fork()==0 ) {
                respond(slot);
                exit(0);
            }
        }
        while (clients[slot]!=-1) slot = (slot+1)%CONNMAX;
    }

    return 0;
}

//start server
void startServer(char *port)
{
    struct addrinfo hints, *res, *p;

    // getaddrinfo for host
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo( NULL, port, &hints, &res) != 0) {
        perror ("getaddrinfo() error");
        exit(1);
    }
    // socket and bind
    for (p = res; p!=NULL; p=p->ai_next) {
        listenfd = socket (p->ai_family, p->ai_socktype, 0);
        if (listenfd == -1) continue;
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
    }
    if (p==NULL) {
        perror ("socket() or bind()");
        exit(1);
    }
    freeaddrinfo(res);

    // listen for incoming connections
    if ( listen (listenfd, 1000000) != 0 ) {
        perror("listen() error");
        exit(1);
    }
}

//client connection

//using namespace std;

// set headers (or use directly from map)
//req.hostName_ = headers["Host"];
//req.conn_ = headers["Connection"];
//req.accept_ = headers["Accept"];
//req.acceptLanguage_ = headers["Accept-Language"];
//req.acceptEncoding_ = headers["Accept-Encoding"];
//req.userAgent_ = headers["User-Agent"];

#if 0
//bool isthat(char c, char t)
//{
//    if (c == t) return true;
//    return false;
//}

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string_size j = i;
        while (j != s.size() && !isspace(s[j]))
            ++j;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}
#endif

void respond(int n)
{
    char mesg[99999], *reqline[8], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;

    memset( (void*)mesg, (int)'\0', 99999 );
    rcvd=recv(clients[n], mesg, 99999, 0);
    //string message(mesg);
    printf("<<< start-message >>>\n");
    printf("rcv'd message: %s\n", mesg);
    printf("<<<  end message  >>>\n\n");
    //vector<string> vs = split(message);

    if (rcvd<0) // receive error
        fprintf(stderr,("recv() error\n"));
    else if (rcvd==0)    // receive socket closed
        fprintf(stderr,"Client disconnected upexpectedly.\n");
    else {  // message received
        reqline[0] = strtok (mesg, " \t\n");
        //printf("reqline[0]: %s\n", reqline[0]);
        if ( strncmp(reqline[0], "GET\0", 4)==0 ) {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            reqline[3] = strtok (NULL, " \t\n");
            reqline[4] = strtok (NULL, " \t\n");
            reqline[5] = strtok (NULL, " \t\n");
            reqline[6] = strtok (NULL, " \t\n");
            reqline[7] = strtok (NULL, " \t\n");
            //printf("reqline[1]: %s\n", reqline[1]);
            //printf("reqline[2]: %s\n", reqline[2]);
            //printf("reqline[3]: %s\n", reqline[3]);
            //printf("reqline[4]: %s\n", reqline[4]);
            //printf("reqline[5]: %s\n", reqline[5]);
            //printf("reqline[6]: %s\n", reqline[6]);
            //printf("reqline[7]: %s\n", reqline[7]);
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && 
                 strncmp( reqline[2], "HTTP/1.1", 8)!=0 ) {
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            } else {
                if ( strncmp(reqline[1], "/\0", 2)==0 ) {
                    // Because if no file is specified, index.html will be 
                    // opened by default (like it happens in APACHE...
                    reqline[1] = (char *) "/src/index.html";
                }
                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], reqline[1]);
                printf("file: %s\n", path);
                if ( (fd=open(path, O_RDONLY))!=-1 ) {  //FILE FOUND
                    send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[n], data_to_send, bytes_read);
                } else {
                    write(clients[n], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
                }
            }
        }
    }
    //All further send and recieve operations are DISABLED...
    shutdown (clients[n], SHUT_RDWR);
    close(clients[n]);
    clients[n]=-1;
}

