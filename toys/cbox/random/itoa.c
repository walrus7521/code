#include <stdio.h>
#include <string.h>

#define RADIX_10            (10)
#define HEX_NUM_OFFSET      (10)
#define ALPHA_ZERO          ('0')
#define HEX_TEN             ('a')
#define MINUS_SIGN          ('-')

int my_itoa(int value, char *sp, int radix)
{
    char tmp[16];       // string buffer for result
    char *tp = tmp;     // pointer to string buffer
    int i;              // decimal place value
    int len;            // length of string returned
    unsigned int v;     // radix variable


    int sign = (radix == RADIX_10 && value < 0);    
    if (sign) 
    {
        v = -value;
    } 
    else 
    {
        v = (unsigned int) value;
    }

    // string is populated in reverse
    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
        {
            // decimal or hex numeric digit
            *tp++ = i + '0';
        }
        else
        {
            // hex alpha digit
            *tp++ = i + 'a' - 10;
        }
    }

    len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    // reverse the string
    while (tp > tmp)
    {
        *sp++ = *--tp;
    }
    *sp = '\0'; // null terminate

    return len;
}


int main()
{
    int a = 0xdea1;
    char buffer[20];

//    memset(buffer, 0, 20);
//    my_itoa(a, buffer, 2);   // here 2 means binary
//    printf("Binary value = %s\n", buffer);
 
//    memset(buffer, 0, 20);
//    my_itoa(a, buffer, 10);   // here 10 means decimal
//    printf("Decimal value = %s\n", buffer);
 
    memset(buffer, 0, 20);
    my_itoa(a, buffer, 16);   // here 16 means Hexadecimal
    printf("Hexadecimal value = 0x%s\n", buffer);
}

