#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char one[5][3] = {
    ' ',' ',' ',
    ' ',' ','|',
    ' ',' ',' ',
    ' ',' ','|',
    ' ',' ',' ',
};
char two[5][3] = {
    ' ','-',' ',
    ' ',' ','|',
    ' ','-',' ',
    '|',' ',' ',
    ' ','-',' ',
};
char three[5][3] = {
    ' ','-',' ',
    ' ',' ','|',
    ' ','-',' ',
    ' ',' ','|',
    ' ','-',' ',
};
char four[5][3] = {
    ' ',' ',' ',
    '|',' ','|',
    ' ','-',' ',
    ' ',' ','|',
    ' ',' ',' ',
};
char five[5][3] = {
    ' ','-',' ',
    '|',' ',' ',
    ' ','-',' ',
    ' ',' ','|',
    ' ','-',' ',
};
char six[5][3] = {
    ' ','-',' ',
    '|',' ',' ',
    ' ','-',' ',
    '|',' ','|',
    ' ','-',' ',
};
char seven[5][3] = {
    ' ','-',' ',
    ' ',' ','|',
    ' ',' ',' ',
    ' ',' ','|',
    ' ',' ',' ',
};
char eight[5][3] = {
    ' ','-',' ',
    '|',' ','|',
    ' ','-',' ',
    '|',' ','|',
    ' ','-',' ',
};
char nine[5][3] = {
    ' ','-',' ',
    '|',' ','|',
    ' ','-',' ',
    ' ',' ','|',
    ' ','-',' ',
};
char zero[5][3] = {
    ' ','-',' ',
    '|',' ','|',
    ' ',' ',' ',
    '|',' ','|',
    ' ','-',' ',
};

char **num_segments[] = {(char **) zero, (char **) one, (char **) two,   (char **) three, (char **) four, 
                         (char **) five, (char **) six, (char **) seven, (char **) eight, (char **) nine};

void segment(char x[5][3], int s)
{
    int c, r, ri, ci, rows, cols, midr;
    cols = s+2;
    rows = 2*s+3;
    midr = rows / 2;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            ri = r; ci = c; // zeros case
            if      (r > 0 && r < midr)      ri = 1;
            else if (r == midr)              ri = 2;
            else if (r > midr && r < rows-1) ri = 3;
            else if (r == rows-1)            ri = 4;
            if      (c > 0 && c < cols-1)    ci = 1;
            else if (c == cols-1)            ci = 2;
            printf("%c", x[ri][ci]);
        }
        printf("\n");
    }
    printf("\n");
}

void outrow(char x[5][3], int row, int s)
{
    int c, ci, cols;
    cols = s+2;
    for (c = 0; c < cols; c++) {
        ci = c;
        if      (c > 0 && c < cols-1)    ci = 1;
        else if (c == cols-1)            ci = 2;
        printf("%c", x[row][ci]);
    }
}

void lcd_display(int cnt, char ***anum, int s)
{
    int n, r, ri, rows, midr, seg;
    rows = 2*s+3;
    midr = rows / 2;
    //for (n = 0; n < cnt; n++) segment((char (*)[3]) anum[n], s);
    //return;
    for (r = 0; r < rows; r++) {
        ri = r;
        if      (r > 0 && r < midr)      ri = 1;
        else if (r == midr)              ri = 2;
        else if (r > midr && r < rows-1) ri = 3;
        else if (r == rows-1)            ri = 4;
        for (seg = 0; seg < cnt; seg++) {
            outrow((char (*)[3]) anum[seg], ri, s);
            if (seg < cnt-1) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n = 0, s = 2, len, inum;
    char line[80] = {0};
    char number[10]; //[]  = "9026598335";
    char **anum[10];

    while (fgets(line, 80, stdin)) {
        sscanf(line, "%d %s\n", &s, number);
        len = strlen(number);
        if (s == 0 && len == 1) {
            inum = number[0] - '0';
            if (inum == 0) return 0;
        }
        for (n = 0; n < len; n++) {
            inum = number[n] - '0';
            anum[n] = num_segments[inum];
        }
        lcd_display(len, anum, s);
        printf("\n");
    }

    return 0;
}

