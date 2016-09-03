#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define DECIMAL_MULTIPLE    (10.0f)
#define SINGLE_DIGIT_MAX    (9)
static int ftoa(float f, int significant, char *buf)
{
    int pos = 0; // initial buffer position
    int ix;      // loop index
    int dp;      // number of digits to left of decimal
    int num;     // integer value of float digit
    int len;     // length of resultant string

    if ( f < 0)
    {
        buf[pos++] = '-';
        f = -f;
    }
    dp = 0;
    // force all but single digit left of decimal
    // and accumulate the number of places shifted
    printf("chk1: f %f\n", f);
    while ( f >= DECIMAL_MULTIPLE) 
    {
        f = f / DECIMAL_MULTIPLE;
        dp++;
    }
    printf("chk2: f %f, dp %d\n", f, dp);
    for (ix = 1; ix < significant; ix++)
    {
        num = f;
        f = f - num;
        printf("chk3: f %f, num %d\n", f, num);
        if (num > SINGLE_DIGIT_MAX) // invalid digit
        {
            printf("woops1: dp %d\n", dp);
            buf[pos++]='#'; // NaN
        }
        else
        {
            printf("woops2: dp %d\n", dp);
            buf[pos++]='0'+num; // number to char conversion
        }
        if (dp == 0) // finished processing digits to left of decimal place
        {
            buf[pos++]='.';
        }
        f = f * DECIMAL_MULTIPLE;
        dp--;
    }
    len = pos;
    return len;
}

int main()
{
    int a = 0xdead;
    float f = 22.0 / 7.0; //3.14;
    char buffer[20];

    memset(buffer, 0, 20);
    f = 123.4;
    ftoa(f, 8, buffer);
    printf("Float value = %s\n", buffer);

    return 0;
}
