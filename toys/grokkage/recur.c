#include <stdio.h>

void mark(int m, int h)
{
    printf("mark at %d, height %d\n", m, h);
}

/* draw marks on a ruler
   h = height of mark */
void ruler1(int l, int r, int h)
{
    int  m = (l+r)/2;
    if (h > 0) {
        mark(m, h); /* mark at midpoint, height h */
        ruler1(l, m, h-1); /* first make all left marks */
        ruler1(m, r, h-1); /* finally, make all right marks */
    }
}

int height(int n)
/* returns ruler height =
   number trailing zeros in binary rep of n */
{
    int count = 0;
    while ((n & 1) == 0) {
        n = n >> 1;
        count++;
    }
    return count+1;
}

void ruler2(int l, int r, int h)
/* draws marks in left -> right order */
{
    /* here r is the number of marks */
    int i;
    for (i = 1; i < r; i++) {
        mark(i, height(i));
    }
}

int main()
{
    int n_marks = 8;
    int max_height = 3; // of midpoint
    printf("ruler1\n");
    ruler1(0, n_marks, max_height);
    printf("ruler2\n");
    ruler2(0, n_marks, max_height);
}

