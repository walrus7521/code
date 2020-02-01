#include <stdio.h>

int lookup(int a[][2], int rows, int value)
{
    int i, index;
    if (value < a[0][0]) return 0;
    
    for (i = 1; i < rows; i++) {
        if (value < a[i][0]) return i;
    }
    return rows-1;
}


int main()
{
    int row;
    int arry[3][2] = {{10, 2}, // breaks and slopes
                      {20, 5}, 
                      {30, 4}};

    for (row = 0; row < 3; row++) {
        printf("%03d : %03d\n", arry[row][0], arry[row][1]);
    }

    int rows = 3;
    int value;
    int idx;
    int slope;
    value = 1;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    printf("lookup: %d slope: %d\n", value, slope);
    value = 10;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    printf("lookup: %d slope: %d\n", value, slope);
    value = 15;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    printf("lookup: %d slope: %d\n", value, slope);
    value = 20;
    idx = lookup(arry, rows, value);
    slope = arry[idx][1];
    printf("lookup: %d slope: %d\n", value, slope);

    return 0;
}

