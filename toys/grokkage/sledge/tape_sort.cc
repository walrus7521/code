#include <stdio.h>
#include <string.h>
#include <math.h>

// sedgewick

#define MAXN 100

void arr_show(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) printf("%c ", a[i]);
    printf("\n");
}

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void selsort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        swap(a, i, min);
    }
}

int smallest(int a[], int n)
{
    int i, min = 9999999, min_idx = -1;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min_idx = i;
            min = a[i];
        }
    }
    return min_idx;
}

void append(int tape[], int i, int buf[], int j, int n)
{
    int it, ib;
    printf("append: tape %d <= buf %d len %d\n", i, j, n);
    for (it = i, ib = j; ib < n; it++, ib++) {
        tape[it] = buf[ib];
    }
}

#define MIN(a, b) (((a)>(b)) ? (b) : (a))

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
    int s1=3, s2=3, s3=3;
    tmp[0] = tape1[0];
    tmp[1] = tape2[0];
    tmp[2] = tape3[0];
    for (n = 1; n < 9; n++) {
        small = smallest(tmp, 3);
        tape4[n] = tmp[small];
        s1--; s2--; s3--;
        printf("%c %c %c => %c\n", tmp[0], tmp[1], tmp[2], tmp[small]);
        switch (small) {
            case 0: tmp[small] = tape1[n]; break;
            case 1: tmp[small] = tape2[n]; break;
            case 2: tmp[small] = tape3[n]; break;
        }
    }
    arr_show(tape4, n);
}

int main()
{

    three_way_merge_sort();

}

