#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"

char devname[] = "/dev/gen0";

/* char devname[] = "/dev/gen0n1";
 * dev/scsi/host0/bus0/target0/lun0/disc
 * dev/scsi/host0/bus0/target0/lun0/part1
 */

void input_handler(int signal)
{
    printf("got a signal %d\n", signal);
}

int main(int argc, char *argv[])
{
    int c, cmd=0, i;
    int ret, fd;
    __u8 feat=0;
    __u32 hval=0;
    __u32 num=0;
    __u16 qid=1;
  __u16 depth=1;
  __u32 oflags;

    fd = open(devname, O_RDWR);
    if (fd < 0) {
        printf("failed to open %s err %d\n", devname, errno);
        exit(1);
    }
    
    signal(SIGIO, &input_handler);
    fcntl(fd, F_SETOWN, getpid());
    oflags = fcntl(fd, F_GETFL);
    printf("oflags = %x\n", oflags);
    fcntl(fd, F_SETFL, oflags | FASYNC);

    while (1) ;

    close(fd);
	
    return 0;
}

