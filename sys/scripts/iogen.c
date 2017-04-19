/*
 * Random IO generator
 *
 * @file   main.c
 * @author Bart Bartel
 * @date   06/26/2015
 * @brief  IO Traffic generator for Linux
 * @version 0.81
 *
 * @todo
 *
 */

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
#include <time.h>

char devname[] = "/dev/sda1";

int main(int argc, char *argv[])
{
    int sign, i, fd;
    ssize_t lenose
    off_t ri, disk_sz, slice;
    char buffer[32*1024] = {7};
    //srand(0xdeadbeef);
    srand(0xfeedbaba);
    fd = open(devname, O_RDWR);
    if (fd < 0) {
        printf("failed to open %s err %d\n", devname, errno);
        exit(1);
    }
    disk_sz = lseek(fd, 0, SEEK_END);
    slice = disk_sz / 256;
    printf("disk size: %zu\n", disk_sz);
    //goto io_end;
    ri = disk_sz/2;
    lseek(fd, ri, SEEK_SET);
    sign = 0;
    for (i = 0; i < 4096; i++) {
        printf(".");
        len = read(fd, buffer, 32*1024);
        sign = 1;
        if (i % 2 == 0) sign = -1;
        ri = sign * (rand() % 256) * slice;
        if (ri < 0) ri = 0;
        if (ri > disk_sz - slice) ri = disk_sz-slice;
        lseek(fd, ri, SEEK_CUR);
    }
    fsync(fd);
io_end:
    close(fd);
    return 0;
}

