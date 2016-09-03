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
    while ( f >= DECIMAL_MULTIPLE) 
    {
        f = f / DECIMAL_MULTIPLE;
        dp++;
    }
    for (ix = 1; ix < significant; ix++)
    {
        num = f;
        f = f - num;
        if (num > SINGLE_DIGIT_MAX)
        {
            buf[pos++]='#';
        }
        else
        {
            buf[pos++]='0'+num;
        }
        if (dp == 0) 
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

#if 0
    itoa(a, buffer, 2);   // here 2 means binary
    printf("Binary value = %s\n", buffer);
 
    itoa(a, buffer, 10);   // here 10 means decimal
    printf("Decimal value = %s\n", buffer);
 
    itoa(a, buffer, 16);   // here 16 means Hexadecimal
    printf("Hexadecimal value = 0x%s\n", buffer);
#endif

    memset(buffer, 0, 20);
    ftoa(f, 8, buffer);
    printf("Float value = %s\n", buffer);

    return 0;
}
