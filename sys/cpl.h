#ifndef _LINUX_PQI_H
#define _LINUX_PQI_H

#include <linux/types.h>

#define cplu_test_queue 0x99
struct cplu_cmd {
    int op;
    __u64 data;
    int qid;
    int depth;
    int time;
    int num;
    int status;
    int debug;
};

#define CPLU_IOCTL_PASS_THROUGH _IOWR('P', 0x71, struct cplu_cmd)

#endif /* _LINUX_PQI_H */
