#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define DECIMAL_MULTIPLE    (10.0f)
#define SINGLE_DIGIT_MAX    (9)
static int ftoa(float f, int significant, char *buf)
{
    int pos = 0; // initial buffer position
    int ix;      // loop index
    int dp;      // digit counter
    int num;     // integer value of a float digit
    int len;     // length of resultant string

    if ( f < 0)
    {
        buf[pos++] = '-';
        f = -f;
    }

    dp = 0; // set number of decimals to zero
    // force all but single digit left of decimal
    // and accumulate the number of places shifted
    while ( f >= DECIMAL_MULTIPLE) 
    {
        f = f / DECIMAL_MULTIPLE;
        dp++;
    }
    // dp now contains the number of decimals shifted
    // left such that f > 0.0 and < 10.0
    // f will be of the form w.xyz...
    for (ix = 1; ix < significant; ix++)
    {
        // peel off leading digit
        num = f;
        // remove leading digit, 
        // next digit will be shifted over below
        f = f - num;
        if (num > SINGLE_DIGIT_MAX) // invalid digit
        {
            buf[pos++]='#'; // NaN
        }
        else
        {
            buf[pos++]='0'+num; // number to char conversion
        }
        if (dp == 0) // finished processing digits to left of decimal place
        {            // remaining digits will be right of decimal
            buf[pos++]='.';
        }
        f = f * DECIMAL_MULTIPLE; // shift next digit over
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
