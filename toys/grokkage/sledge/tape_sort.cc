#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sedgewick.h"

int smallest(int a[], int n)
{
    int i, min = 9999999, min_idx = -1;
    for (i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        if (a[i] < min) {
            min_idx = i;
            min = a[i];
        }
    }
    return min_idx;
}

int num_alphas(int a[], int n)
{
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if ('A' <= a[i] && a[i] <= 'Z') count++;
        else if ('a' <= a[i] && a[i] <= 'z') count++;
    }
    return count;
}

int tape_in[] = {'A','S','O','R','T','I','N','G','A','N','D','M','E', \
                 'R','G','I','N','G','E','X','A','M','P','L','E'};
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
    tmp[0] = tmp[1] = tmp[2] = 0;
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
        arr_show(&tape1[n/3], 0, t1_lim-n/3);
        for (k=0,t2 = n/3; t2 < t2_lim; t2++, j++, k++) {
            //printf("t2: %02d j: %02d :%c\n", t2, j, tape_in[j]);
            tmp[k] = tape_in[j];
        }
        selsort(tmp, t2_lim-n/3);
        append(tape2, n/3, tmp, 0, t2_lim-n/3);
        arr_show(&tape2[n/3], 0, t2_lim-n/3);
        for (k=0,t3 = n/3; t3 < t3_lim; t3++, j++, k++) {
            //printf("t3: %02d j: %02d :%c\n", t3, j, tape_in[j]);
            tmp[k] = tape_in[j];
        }
        selsort(tmp, t3_lim-n/3);
        append(tape3, n/3, tmp, 0, t3_lim-n/3);
        arr_show(&tape3[n/3], 0, t3_lim-n/3);
    }
    arr_show(tape1, 0, n);
    arr_show(tape2, 0, n);
    arr_show(tape3, 0, n);

    // now ready to merge the sorted sub-blocks
    // process the 1st 3x3 block into tape4
    // process the 2nd 3x3 block into tape5
    // process the 3rd 3x3 block into tape6

#define MAX_DATA_IDX (2)
    int n_blocks = (len / 9);
    int rem_blocks = n_blocks % 9;
    if (rem_blocks > 0) {
        n_blocks++;
    }
    printf("start merging %d blocks, rem %d\n", n_blocks, rem_blocks);
    int b;
    int offset;
    b = 2;
    //for (b = 0; b < n_blocks; b++) 
    {
        int *tape_out; // pointer to current tape
        switch (b) {
            case 0: tape_out = tape4; break;
            case 1: tape_out = tape5; break;
            case 2: tape_out = tape6; break;
            default: printf("bad tape\n");
        }
        n = 0;
        offset = b * 3;
        int small; // index of tape with smallest value
        int small_idx;
        int tape_idx[3] = {0,0,0};
        int count1 = num_alphas(&tape1[offset], 3);
        int count2 = num_alphas(&tape2[offset], 3);
        int count3 = num_alphas(&tape3[offset], 3);
        int tape_max[3] = {count1, count2, count3};
        int n_len = count1 + count2 + count3;
        printf("n_len: %d\n", n_len);
        printf("num alphas: %d,%d,%d\n", tape_max[2],tape_max[1],tape_max[0]);
        unsigned char tape_mask = 0; // initialize mask to 0b111
        tmp[0] = tmp[1] = tmp[2] = 0;
        if (tape_max[0]) {
            tape_mask |= 1;
            tmp[0] = tape1[offset+tape_idx[0]++];
            printf("0) ");
            arr_show(&tape1[offset], 0, 3);
        }
        if (tape_max[1]) {
            tape_mask |= 2;
            tmp[1] = tape2[offset+tape_idx[1]++];
            printf("1) ");
            arr_show(&tape2[offset], 0, 3);
        }
        if (tape_max[2]) {
            tape_mask |= 4;
            tmp[2] = tape3[offset+tape_idx[2]++];
            printf("2) ");
            arr_show(&tape3[offset], 0, 3);
        }
        arr_show(tmp, 0, 3);
        tape_max[0]--; tape_max[1]--; tape_max[2]--; // convert to indices
        printf("block: %d, offset: %d\n", b, offset);
        small = smallest(tmp, 3);
        small_idx = small;
        tape_out[n] = tmp[small];
        if (tape_idx[small_idx] > tape_max[small_idx]) {
            tape_mask &= ~(1 << small_idx);
        }

        printf("%d> %c %c %c => %d=%c\n", n, tmp[2], tmp[1], tmp[0], small, tmp[small]);
        printf("idx> %d : %d %d %d => mask %02x\n\n", small_idx, tape_idx[2], tape_idx[1],
                                                      tape_idx[0],tape_mask);
        for (n = 1; n < n_len; n++) { // 7 REMREMREMREMREM
            switch (tape_mask) {
                case 0x00: // no data left
                    printf("semi-final array: %d\n", n);
                    arr_show(tape_out, 0, n);
                    printf("zeros show tmp: %d\n", n);
                    selsort(tmp, 3);
                    arr_show(tmp, 0, 3);
                    count1 = num_alphas(tmp, 3);
                    printf("final tmp count: %d, idx: %d\n", count1, small_idx);
                    tape_out[n] = tmp[1]; // !!! Ok for n = 9
                    tape_out[n+1] = tmp[2]; // !!!
                    //tape_out[n] = tmp[2]; // for n = 7 BUGBUG
                    goto done;
                    break;
                case 0x01: // only tape 1
                    tmp[small] = tape1[offset+tape_idx[0]++];
                    small_idx = 0;
                    break;
                case 0x02: // only tape 2
                    tmp[small] = tape2[offset+tape_idx[1]++];
                    small_idx = 1;
                    break;
                case 0x04: // only tape 3
                    tmp[small] = tape3[offset+tape_idx[2]++];
                    small_idx = 2;
                    break;
                case 0x03: // tapes 1 and 2
                    if (tape1[offset+tape_idx[0]] < tape2[offset+tape_idx[1]]) {
                        tmp[small] = tape1[offset+tape_idx[0]++];
                        small_idx = 0;
                    } else {
                        tmp[small] = tape2[offset+tape_idx[1]++];
                        small_idx = 1;
                    }
                    break;
                case 0x05: // tapes 1 & 3
                    if (tape1[offset+tape_idx[0]] < tape3[offset+tape_idx[2]]) {
                        tmp[small] = tape1[offset+tape_idx[0]++];
                        small_idx = 0;
                    } else {
                        tmp[small] = tape3[offset+tape_idx[2]++];
                        small_idx = 2;
                    }
                    break;
                case 0x06: // tapes 2 & 3
                    printf("mask6: tape2: %c tape3: %c\n", tape2[offset+tape_idx[1]], tape3[offset+tape_idx[2]]);
                    if (tape2[offset+tape_idx[1]] < tape3[offset+tape_idx[2]]) {
                        tmp[small] = tape2[offset+tape_idx[1]++];
                        small_idx = 1;
                    } else {
                        tmp[small] = tape3[offset+tape_idx[2]++];
                        small_idx = 2;
                    }
                    printf("6: tmp[%d] was replaced with %c\n", small, tmp[small]);
                    break;
                case 0x07: // all tapes
                    switch (small) {
                        case 0:
                            tmp[small] = tape1[offset+tape_idx[0]++];
                            small_idx = 0;
                            break;
                        case 1:
                            tmp[small] = tape2[offset+tape_idx[1]++];
                            small_idx = 1;
                            break;
                        case 2:
                            tmp[small] = tape3[offset+tape_idx[2]++];
                            small_idx = 2;
                            break;
                    }
                    break;
            }

            printf("tmp[%d] was replaced with %c\n", small, tmp[small]);
            small = smallest(tmp, 3);
            tape_out[n] = tmp[small];
            printf("chk bits: small: %d, idx: %d\n", small_idx, tape_idx[small_idx]);
            if (tape_idx[small_idx] > tape_max[small_idx]) { //MAX_DATA_IDX) {
                tape_mask &= ~(1 << small_idx);
                printf("clearing bit %d => mask: %x\n", small_idx, tape_mask);
            }
            printf("%d> %c %c %c => %d=%c\n", n, tmp[2], tmp[1], tmp[0], small, tmp[small]);
            printf("idx> %d : %d %d %d => mask %02x\n\n", small_idx, tape_idx[2], tape_idx[1], tape_idx[0], tape_mask);
        }
done:
        printf("final array: %d->%d\n", b*9, b*9+n_len);
        arr_show(tape_out, 0, n_len);
    }
    printf("dump all tapes\n");
    arr_show(tape4, 0, 9);
    arr_show(tape5, 0, 9);
    arr_show(tape6, 0, 9);
}

