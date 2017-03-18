#include <stdio.h>
#include <stdlib.h>

int H[16] = {0};
int hcount = 0;

void swap(int *a, int i, int j) {
    int tmp;
    //printf("swap(a[%d]:%d, a[%d]:%d)\n", i, a[i], j, a[j]);
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void printtree(int s[], int count) {
    int i, level, j, k;
    int lvl[] = {0, 1,  2,  2,  4,  4,  4,  4, \
                    8,  8,  8,  8,  8,  8,  8,  8, \
                   16, 16, 16, 16, 16, 16, 16, 16, \
                   16, 16, 16, 16, 16, 16, 16, 16, 16};
    for (i = 1; i <= count; ) {
        level = lvl[i];
        switch (level) {
            case 1: printf("        "); break;
            case 2: printf("      "); break;
            case 4: printf("  "); break;
        }
        //printf("lvl %d i=%d\n", level, i);
        for (j = i, k = 1; (k <= level) && (i <= count); ++k, ++j) {
            printf("[%d] ", s[j]);
            ++i;
        }
        printf("\n");
    }
}

void show(int *a, int sz) {
    int i;
    for (i = 1; i <= sz; ++i) {
        printf("[%d] , ", a[i]);
    }
    printf("\n");
}

void min_siftdown() {
    int i = 1, l, r, pos;
    i = 1;
    while (i <= hcount) {
        l = 2*i;
        r = l+1;
        if (H[l] > H[r]) pos = r;
        else pos = l;
        if ((l <= hcount) && (H[i] > H[pos])) {
            swap(H, i, pos);
            i = pos;
        } else {
            break;
        }
    }
}

void max_siftdown() {
    int i = 1, l, r, pos;
    i = 1;
    while (i <= hcount) {
        l = 2*i;
        r = l+1;
        if (H[l] > H[r]) pos = l;
        else pos = r;
        if ((l <= hcount) && (H[i] < H[pos])) {
            swap(H, i, pos);
            i = pos;
        } else {
            break;
        }
    }
}

void min_siftup() {
    int i = hcount;
    int x;
    x = H[hcount];
    while (i > 1) {
        if (H[i] < H[i/2]) swap(H, i, i/2);
        i /=2;
    }
}

void max_siftup() {
    int i = hcount;
    int x;
    x = H[hcount];
    while (i > 1) {
        if (H[i] > H[i/2]) swap(H, i, i/2);
        i /=2;
    }
}

int getmin() {
    int min = H[1];
    H[1] = H[hcount];
    hcount--;
    min_siftdown();
    return min;
}

int getmax() {
    int max = H[1];
    H[1] = H[hcount];
    hcount--;
    max_siftdown();
    return max;
}

void min_hsort(int x) {
    hcount++;
    H[hcount] = x;
    //printf("insert: %d\n", x);
    min_siftup();
    //show(H, 8);
}

void max_hsort(int x) {
    hcount++;
    H[hcount] = x;
    //printf("insert: %d\n", x);
    max_siftup();
    //show(H, 8);
}

void min_test()
{
    int x[] = {1,3,5,7,2,4,6,8};
    int i, sz=sizeof(x)/sizeof(x[0]), min;
    hcount = 0;
    show(x, sz);
    for (i = 0; i < sz; i++)
        min_hsort(x[i]);
    printtree(H, hcount);
    printf("\n");
    while (hcount) {
        min = getmin();
        printf("min = %d\n", min);
        printtree(H, hcount);
    }
    printf("\n");
}

void max_test()
{
    int x[] = {1,3,5,7,2,4,6,8};
    int i, sz=sizeof(x)/sizeof(x[0]), max;
    hcount = 0;
    show(x, sz);
    for (i = 0; i < sz; i++)
        max_hsort(x[i]);
    printtree(H, hcount);
    printf("\n");
    while (hcount) {
        max = getmax();
        printf("max = %d\n", max);
        printtree(H, hcount);
    }
    printf("\n");
}

void heap_play();
int main()
{
    int i;
    min_test();
    max_test();
    return 0;
}

void heap_play() {
    int right, left, parent, i;
    int t[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, \
               17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

    for (i = 1; i <= 32; ++i) {
        parent = i;
        left  = 2*parent;
        right = left+1;
        if (parent == 0) left = right = -1;
        if (left > 31) left = -1;
        if (right > 31) right = -1;
        printf("parent: %02d -> left[%02d] | right[%02d]\n", parent, left, right);
    }
    for (i = 32; i > 0; --i) {
        if (i % 2) {
            left = i;
            parent = (i)/2;
            if (parent == 0) parent = -1;
            printf("left:  %02d -> parent[%02d]\n", left, parent);
        } else {
            right = i;
            parent = (i)/2;
            if (parent == 0) parent = -1;
            printf("right: %02d -> parent[%02d]\n", right, parent);
        }
    }
    printtree(t, 32);
}

