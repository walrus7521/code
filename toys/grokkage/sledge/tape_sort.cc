#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sedgewick.h"

int tape_in[] = {'A','S','O','R','T','I','N','G','A','N','D','M','E','R','G','I','N','G','E','X','A','M','P','L','E'};
int tape_out[32] = {0};
void three_way_merge_sort()
{
    int n, t1, t2, t3, j, k;
    int t1_lim, t2_lim, t3_lim;
    int len = sizeof(tape_in) / sizeof(tape_in[0]);
    int remainder;
    int tmp[3];
    int tape1[32] = {0};
    int tape2[32] = {0};
    int tape3[32] = {0};
    int tape4[32] = {0};
    int tape5[32] = {0};
    int tape6[32] = {0};
    printf("len: %d\n", len);
    for (n = 0; n < len; n++) printf("%c ", tape_in[n]);
    printf("\n");
    // fix this loop to manage the non-multiple of 3 size of input
    // this should be reflected on the outputs: tape1, tape2, tape3
    for (j = n = 0; n < len; n+=9) {
        remainder = (25 - n) % 25;
        t1_lim = t2_lim = t3_lim = n/3+3;
        if (remainder > 0 && remainder < 9) {
            printf("gotta fix up this loop\n");
            t1_lim = t2_lim = t3_lim = 0;
            if (remainder < 3) {
                t1_lim = remainder;
            } else
            if (remainder < 6) {
                t1_lim = n/3+3;
                t2_lim = remainder;
                t3_lim = 0;
            } else
            if (remainder < 9) {
                t1_lim = n/3+3;
                t2_lim = n/3+3;
                t3_lim = remainder;
            }
        }

        //printf("n: %d n/3: %d j: %d min: %d rem: %d\n", n, n/3, j, MIN(n,n/3+3), remainder);
        //printf("t1_lim: %d t2_lim: %d t3_lim: %d\n", t1_lim, t2_lim, t3_lim);
        for (k=0,t1 = n/3; t1 < t1_lim; t1++, j++, k++) {
            //printf("t1: %02d j: %02d :%c\n", t1, j, tape_in[j]);
            tmp[k] = tape_in[j];
        }
        selsort(tmp, t1_lim-n/3);
        append(tape1, n/3, tmp, 0, t1_lim-n/3);
        arr_show(&tape1[n/3], t1_lim-n/3);
        for (k=0,t2 = n/3; t2 < t2_lim; t2++, j++, k++) {
            //printf("t2: %02d j: %02d :%c\n", t2, j, tape_in[j]);
            tmp[k] = tape_in[j];
        }
        selsort(tmp, t2_lim-n/3);
        append(tape2, n/3, tmp, 0, t2_lim-n/3);
        arr_show(&tape2[n/3], t2_lim-n/3);
        for (k=0,t3 = n/3; t3 < t3_lim; t3++, j++, k++) {
            //printf("t3: %02d j: %02d :%c\n", t3, j, tape_in[j]);
            tmp[k] = tape_in[j];
        }
        selsort(tmp, t3_lim-n/3);
        append(tape3, n/3, tmp, 0, t3_lim-n/3);
        arr_show(&tape3[n/3], t3_lim-n/3);
    }
    arr_show(tape1, n);
    arr_show(tape2, n);
    arr_show(tape3, n);
    printf("start merge\n");
    int first = 1;
    int small = -1; // index of tape with smallest value
    // now ready to merge the sorted sub-blocks
    // process the 1st 3x3 block into tape4
    // process the 2nd 3x3 block into tape5
    // process the 3rd 3x3 block into tape6
#define MAX_DATA_IDX (2)
    n = 0;
    int tape_idx[3] = {0,0,0};
    unsigned char tape_mask = 0x07; // 111
    // prime the reads
    tmp[0] = tape1[tape_idx[0]++];
    tmp[1] = tape2[tape_idx[1]++];
    tmp[2] = tape3[tape_idx[2]++];
    small = smallest(tmp, 3);
    tape4[n] = tmp[small];
    if (tape_idx[small] > MAX_DATA_IDX) {
        tape_mask &= ~(1 << small);
    }
    printf("%d> %c %c %c => %d=%c\n", n, tmp[0], tmp[1], tmp[2], small, tmp[small]);
    printf("idx> %d %d %d => mask %02x\n", tape_idx[0],tape_idx[1],tape_idx[2],tape_mask);

    for (n = 1; n < 9; n++) {

        switch (tape_mask) {
            case 0x00: // no data left
                //goto done;
                break;
            case 0x01: // only tape 1
                tmp[small] = tape1[tape_idx[0]++];
                break;
            case 0x02: // only tape 2
                tmp[small] = tape2[tape_idx[1]++];
                break;
            case 0x04: // only tape 3
                tmp[small] = tape3[tape_idx[2]++];
                break;
            case 0x03: // tapes 1 and 2
                if (tape1[tape_idx[0]] < tape2[tape_idx[1]]) {
                    tmp[small] = tape1[tape_idx[0]++];
                } else {
                    tmp[small] = tape2[tape_idx[1]++];
                }
                break;
            case 0x05: // tapes 1 & 3
                if (tape1[tape_idx[0]] < tape3[tape_idx[2]]) {
                    tmp[small] = tape1[tape_idx[0]++];
                } else {
                    tmp[small] = tape3[tape_idx[2]++];
                }
                break;
            case 0x06: // tapes 2 & 3
                if (tape2[tape_idx[0]] < tape3[tape_idx[2]]) {
                    tmp[small] = tape2[tape_idx[1]++];
                } else {
                    tmp[small] = tape3[tape_idx[2]++];
                }
                break;
            case 0x07: // all tapes
                switch (small) {
                    case 0:
                        tmp[small] = tape1[tape_idx[0]++];
                        break;
                    case 1:
                        tmp[small] = tape2[tape_idx[1]++];
                        break;
                    case 2:
                        tmp[small] = tape3[tape_idx[2]++];
                        break;
                }
                break;
        }
        small = smallest(tmp, 3);
        tape4[n] = tmp[small];
        if (tape_idx[small] > MAX_DATA_IDX) {
            tape_mask &= ~(1 << small);
        }
        printf("%d> %c %c %c => %d=%c\n", n, tmp[0], tmp[1], tmp[2], small, tmp[small]);
        printf("idx> %d %d %d => mask %02x\n", tape_idx[0],tape_idx[1],tape_idx[2],tape_mask);
    }
done:
    arr_show(tape4, n);
}

