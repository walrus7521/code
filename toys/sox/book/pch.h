#ifndef _PCH_H_
#define _PCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


#define CHK_ERROR(z, msg) { \
    if (z < 0) { \
        fprintf(stderr, "%s: ", msg); \
        perror(msg); \
        fprintf(stderr, \
                "%s\n", \
                strerror(errno)); \
        return 2; \
    } \
}\


#endif // _PCH_H_

