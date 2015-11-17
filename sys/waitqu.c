#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"

char devname[] = "/dev/gen0";

/*
 * usage:  -c 2 genu_start_wait
 *         -c 3 genu_satisfy_wait
 *
 *         -c 4 genu_add_wait
 *         -c 5 genu_wakeup
 *
 */
/* char devname[] = "/dev/gen0n1";
 * dev/scsi/host0/bus0/target0/lun0/disc
 * dev/scsi/host0/bus0/target0/lun0/part1
 */

void help()
{
    printf(" -c  0 - help\n");
    printf(" -c  1 - get pci config\n");
    printf(" -c  2 - wait queue\n");
    printf(" -c  3 - satisfy wait\n");
    printf(" -c  4 - add wait\n");
    printf(" -c  5 - wake up\n");
    printf(" -c  6 - poll\n");
    printf(" -c  7 - signal\n");
    printf(" -c  8 - pause thread\n");
    printf(" -c  9 - resume thread\n");
}

int get_pci_config(int fd)
{
    struct genu_cmd cmd;
    __u32 *vendor;
    struct PCI_COMMON_HEADER *pcihd = &cmd.pci.pci_hdr;
    memset((void *) &cmd, 0, sizeof(cmd));
    cmd.op = genu_get_pci_cfg;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("failed ioctl err %d\n", errno);
    } else {
    printf("PCI Configuration Space:\n");
    printf("Common Header:\n");
    printf("    00: VendorID        %04x\n", pcihd->VendorID);
    printf("    02: DeviceID        %04x\n", pcihd->DeviceID);
    printf("    04: Command         %04x\n", pcihd->Command);
    printf("    06: Status          %04x\n", pcihd->Status);
    printf("    08: RevisionID      %02x\n", pcihd->RevisionID);
    printf("    09: ProgIF          %02x\n", pcihd->ProgIf);
    printf("    0a: SubClass        %02x\n", pcihd->SubClass);
    printf("    0b: BaseClass       %02x\n", pcihd->BaseClass);
    printf("    0c: CacheLineSize   %04x\n", pcihd->CacheLineSize);
    printf("    0d: LatencyTimer    %02x\n", pcihd->LatencyTimer);
    printf("    0e: HeaderType      %02x\n", pcihd->HeaderType);
    printf("    0f: BIST            %02x\n", pcihd->BIST);
    /* _PCI_HEADER_TYPE_0 */
    printf("    10: BAR0            %08x\n", pcihd->BaseAddresses[0]);
    printf("    14: BAR1            %08x\n", pcihd->BaseAddresses[1]);
    printf("    18: BAR2            %08x\n", pcihd->BaseAddresses[2]);
    printf("    1c: BAR3            %08x\n", pcihd->BaseAddresses[3]);
    printf("    20: BAR4            %08x\n", pcihd->BaseAddresses[4]);
    printf("    24: BAR5            %08x\n", pcihd->BaseAddresses[5]);
    printf("    28: CBCISPtr        %08x\n", pcihd->CIS);
    printf("    2c: SubSysVenID     %04x\n", pcihd->SubVendorID);
    printf("    2e: SubSysID        %04x\n", pcihd->SubSystemID);
    printf("    30: ROMBAR          %08x\n", pcihd->ROMBaseAddress);
    printf("    34: CapPtr          %02x\n", pcihd->CapabilitiesPtr);
    printf("    3c: IntLine         %02x\n", pcihd->InterruptLine);
    printf("    3d: IntPin          %02x\n", pcihd->InterruptPin);
    printf("    3e: MinGnt          %02x\n", pcihd->MinimumGrant);
    printf("    3f: MaxLat          %02x\n", pcihd->MaximumLatency);
    printf("Device Private:\n");
    vendor = (__u32 *) &cmd.pci.DeviceSpecific;
    printf("    40: %08x %08x %08x %08x \n",  
            vendor[0],  vendor[1],  vendor[2],  vendor[3]);
    printf("    50: %08x %08x %08x %08x \n",  
            vendor[4],  vendor[5],  vendor[6],  vendor[7]);
    printf("    60: %08x %08x %08x %08x \n",  
            vendor[8],  vendor[9], vendor[10], vendor[11]);
    printf("    70: %08x %08x %08x %08x \n", 
            vendor[12], vendor[13], vendor[14], vendor[15]);
    printf("    80: %08x %08x %08x %08x \n", 
            vendor[16], vendor[17], vendor[18], vendor[19]);
    printf("    90: %08x %08x %08x %08x \n", 
            vendor[20], vendor[21], vendor[22], vendor[23]);
    printf("    a0: %08x %08x %08x %08x \n", 
            vendor[24], vendor[25], vendor[26], vendor[27]);
    printf("    b0: %08x %08x %08x %08x \n", 
            vendor[28], vendor[29], vendor[30], vendor[31]);
    printf("    c0: %08x %08x %08x %08x \n", 
            vendor[32], vendor[33], vendor[34], vendor[35]);
    printf("    d0: %08x %08x %08x %08x \n", 
            vendor[36], vendor[37], vendor[38], vendor[39]);
    printf("    e0: %08x %08x %08x %08x \n", 
            vendor[40], vendor[41], vendor[42], vendor[43]);
    printf("    f0: %08x %08x %08x %08x \n", 
            vendor[44], vendor[45], vendor[46], vendor[47]);
   }
   return 0;
}

int decode_err(int status)
{
    switch (status) {
        case FSC_NOT_IDLE:
            printf("  FSC_NOT_IDLE\n");
            break;
        case DEVICE_STATE_NOT_PD2:
            printf("  DEVICE_STATE_NOT_PD2\n");
            break;
        case DEVICE_STATE_NOT_PD3:
            printf("  DEVICE_STATE_NOT_PD3\n");
            break;
        case MEMORY_ALLOCATION_FAILURE:
            printf("  MEMORY_ALLOCATION_FAILURE\n");
            break;
        case REQUEST_IRQ_FAILED:
            printf("  REQUEST_IRQ_FAILED\n");
            break;
        case ILLEGAL_COMMAND:
            printf("  ILLEGAL_COMMAND\n");
            break;
        case QUEUE_PAIR_CREATE_FAILURE_NO_PD4_ERROR:
            printf("  QUEUE_PAIR_CREATE_FAILURE_NO_PD4_ERROR\n");
            break;
        case QUEUE_PAIR_CREATE_FAILURE_PD4_ERROR:
            printf("  QUEUE_PAIR_CREATE_FAILURE_PD4_ERROR\n");
            break;
        case QUEUE_PAIR_DELETE_FAILURE_PD4_ERROR:
            printf("  QUEUE_PAIR_DELETE_FAILURE_PD4_ERROR\n");
            break;

    }
}

int wait(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_start_wait;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_start_wait err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_start_wait success\n");
    }
    return 0;
}

int satisfy(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_satisfy_wait;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_satisfy_wait err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_satisfy_wait success\n");
    }
    return 0;
}

int add_wait(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_add_wait;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_add_wait err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_add_wait success\n");
    }
    return 0;
}

int wake_up(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_wakeup;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_wakeup err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_wakeup success\n");
    }
    return 0;
}

int do_poll(int fd)
{

    struct pollfd pfds[2];
    pfds[0].fd = 0;
    pfds[0].events = POLLIN;
    pfds[1].fd = fd;
    pfds[1].events = POLLIN;
    poll(pfds, 2, -1);
    return 0;
}

int do_signal(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_send_signal;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_send_signal err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_send_signal success\n");
    }
    return 0;
}

int do_pause(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_pause_thread;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_pause_thread err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_pause_thread success\n");
    }
    return 0;
}

int do_resume(int fd)
{
    struct genu_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.op = genu_resume_thread;
    if (ioctl(fd, GENU_IOCTL_PASS_THROUGH, &cmd) < 0) {
        printf("genu_resume_thread err %d, lineno %d\n", errno, cmd.debug);
        decode_err(cmd.status);
    } else {
        printf("genu_resume_thread success\n");
    }
    return 0;
}

void exec(int hdev, __u8 cmd, __u8 feat, __u32 val, __u16 qid, __u16 depth, __u32 num)
{
    printf("exec(hdev=%x, cmd=%d, feat=%d, val=%d, qid=%d, depth=%d, num=%d)\n", 
        hdev, cmd, feat, val, qid, depth, num);

    switch (cmd) {
        case 0: 
            help(); 
            break;
        case 1: 
            get_pci_config(hdev);
            break;
        case 2: 
            wait(hdev);
            break;
        case 3: 
            satisfy(hdev);
            break;
        case 4: 
            add_wait(hdev);
            break;
        case 5: 
            wake_up(hdev);
            break;
        case 6: 
            do_poll(hdev);
            break;
        case 7: 
            do_signal(hdev);
            break;
        case 8: 
            do_pause(hdev);
            break;
        case 9: 
            do_resume(hdev);
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
        c = getopt(argc, argv, "c:d:f:n:q:v:");
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
            case 'v': 
                sscanf(optarg, "%x", &hval);
                break;
            default:
                break;
        }
    }
    exec(fd, cmd, feat, hval, qid, depth, num);
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

