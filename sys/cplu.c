#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "cpl.h"

char devname[] = "/dev/cpl0";

/* char devname[] = "/dev/cpl0n1";
 * dev/scsi/host0/bus0/target0/lun0/disc
 * dev/scsi/host0/bus0/target0/lun0/part1
 */

void help()
{
    printf(" -c  0  - help\n");
    printf(" -c  17 - test queue\n");
}

int test(int fd)
{
    struct cplu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = cplu_test_queue;
    cmd.qid = 0; /* admin queue */
    if (ioctl(fd, CPLU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("test err %d, lineno %d\n", errno, cmd.debug);
    } else {
        printf("test success\n");
    }
    return 0;
}

void exec(int hdev, __u8 cmd, __u8 feat, __u32 val, __u16 qid, 
        __u16 depth, __u32 num, __u16 time)
{
    printf("exec(hdev=%x, cmd=%d, feat=%d, val=%d, qid=%d, depth=%d, num=%d, time=%d)\n", 
        hdev, cmd, feat, val, qid, depth, num, time);

    switch (cmd) {
        case 0: 
            help(); 
            break;
        case 17: 
            test(hdev);
            break;
    }
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
    __u16 time=1;

    fd = open(devname, O_RDWR);
    if (fd < 0) {
        printf("failed to open %s err %d\n", devname, errno);
        exit(1);
    }
    
    /* 
     * printf("argc=%d\n", argc);
     * for (i = 0; i < argc; i++) {
     *     printf("argv[%d] = %s\n", i, argv[i]);
     * } 
     */


    if (argc <= 1) {
        help();
        return 1;
    }

    while (1) {
        c = getopt(argc, argv, "c:d:f:n:q:t:v:");
        if (c == EOF) break;
        switch (c) {
            case 'c': 
                cmd = atoi(optarg);
                break;
            case 'd': 
                depth = atoi(optarg);
                break;
            case 'f': 
                feat = atoi(optarg);
                break;
            case 'n': 
                num = atoi(optarg);
                break;
            case 'q': 
                qid = atoi(optarg);
                break;
            case 't': 
                time = atoi(optarg);
                break;
            case 'v': 
                sscanf(optarg, "%x", &hval);
                break;
            default:
                break;
        }
    }
    exec(fd, cmd, feat, hval, qid, depth, num, time);
    close(fd);
	
    return 0;
}

void HexDump( __u8 *buffer, __u32 length )
{
    __u8 OffsetBuf[10];
    __u32 LastStart = 0, i, k, j;
    for ( i = 0 ; i < length ; i++ ) {
        if ( i % 16 == 0  ) {
            sprintf( OffsetBuf, "%03x", i );
            printf( "%4s:", OffsetBuf );
        }
        if ( i % 4 == 0 ) {
            printf( " " );
        }
        printf( "%02x ", buffer[i] );
        if ( i % 16 == 15 || i == length-1 ) {
            if ( i == length-1 ) {
                for ( k = i % 16 ; k < 15 ; k++ ) {
                     printf( "   " );
                     if ( k % 4 == 3 && k % 16 != 0 ) {
                         printf( " " );
                     }
                }
            }
            printf( "|" );
            for ( j = LastStart ; j <= i ; j++ ) {
                if ( j % 4 == 0 ) {
                    printf( " " );
                }
                if ( buffer[j] > 31 && buffer[j] < 127 ) {
                    printf( "%c", buffer[j] );
                } else {
                    printf( "." );
                }
            }
            if ( i == length-1 ) {
                printf( "\n" );
                break;
            }
            printf( "\n" );
            LastStart += 16;
        }        
    }
}

