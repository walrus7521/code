/*
    Port scanner code in c
*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
 
// https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers
//
char* port_names[] = {
    "reserved",     // 0
    "mux",          // 1
    "???",          // 2
    "???",          // 3
    "reserved",     // 4
    "remote job",   // 5
    "reserved",     // 6 
    "echo",         // 7
    "reserved",     // 8
    "wake-on-lan",  // 9
    "reserved",  // 10
    "systat",  // 11
    "reserved",  // 12
    "daytime",  // 13
    "reserved",  // 14
    "netstat",  // 15
    "reserved",  // 16
    "qotd",  // 17
    "msg send",  // 18
    "chargen",  // 19
    "ftp data",  // 20
    "ftp ctrl",  // 21
    "ssh",  // 22
    "telnet",  // 23
    "reserved",  // 24
    "smtp",  // 25
    "reserved",  // 26
    "reserved",  // 27
    "reserved",  // 28
    "reserved",  // 29
    "reserved",  // 30
    "reserved",  // 31
    "reserved",  // 32
    "reserved",  // 33
    "reserved",  // 34
    "reserved",  // 35
    "reserved",  // 36
    "time",  // 37
    "rap",  // 38
    "rlp",  // 39
    "reserved",  // 40
    };
int n_port_names = 40;

int main(int argc , char **argv)
{
    struct hostent *host;
    int err, i , sock ,start , end;
    char hostname[100];
    struct sockaddr_in sa;
     
    //Get the hostname to scan
    printf("Enter hostname or IP : ");
    gets(hostname);
     
    //Get start port number
    printf("\nEnter start port number : ");
    scanf("%d" , &start);
     
    //Get end port number
    printf("Enter end port number : ");
    scanf("%d" , &end);
 
    //Initialise the sockaddr_in structure
    strncpy((char*)&sa , "" , sizeof sa);
    sa.sin_family = AF_INET;
     
    //direct ip address, use it
    if(isdigit(hostname[0]))
    {
        printf("Doing inet_addr...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Done\n");
    }
    //Resolve hostname to ip address
    else if( (host = gethostbyname(hostname)) != 0)
    {
        printf("Doing gethostbyname...");
        strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
        printf("Done\n");
    }
    else
    {
        herror(hostname);
        exit(2);
    }
     
    //Start the port scan loop
    printf("~~~~ starting the portscan loop ~~~~ \n");
    for( i = start ; i <= end ; i++) 
    {
        if (i < n_port_names) {
            printf("checking port: %d -> %s      \r", i, port_names[i]);
        } else {
            printf("checking port: %d            \r", i);
        }

        //Fill in the port number
        sa.sin_port = htons(i);
        //Create a socket of type internet
        sock = socket(AF_INET , SOCK_STREAM , 0);
         
        //Check whether socket created fine or not
        if(sock < 0) 
        {
            perror("\nSocket");
            exit(1);
        }
        //Connect using that socket and sockaddr structure
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
         
        //not connected
        if( err < 0 )
        {
            //printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        //connected
        else
        {
            if (i < n_port_names) {
                printf("%-5d open -> %s                 \n", i, port_names[i]);
            } else {
                printf("%-5d open                       \n", i);
            }
        }
        close(sock);
    }
     
    printf("\r");
    fflush(stdout);
    return(0);
} 

