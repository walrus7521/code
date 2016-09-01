#include <stdio.h>
#include <string.h>

int my_itoa(int value, char *sp, int radix)
{
    char tmp[16];
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign) 
    {
        v = -value;
    } 
    else 
    {
        v = (unsigned) value;
    }

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix;
        if (i < 10)
        {
            *tp++ = i+'0';
        }
        else
        {
            *tp++ = i + 'a' - 10;
        }
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
    {
        *sp++ = *--tp;
    }
    sp = '\0';

    return len;
}


int main()
{
    int a = 0xdead;
    char buffer[20];

    memset(buffer, 0, 20);
    my_itoa(a, buffer, 2);   // here 2 means binary
    printf("Binary value = %s\n", buffer);
 
    memset(buffer, 0, 20);
    my_itoa(a, buffer, 10);   // here 10 means decimal
    printf("Decimal value = %s\n", buffer);
 
    memset(buffer, 0, 20);
    my_itoa(a, buffer, 16);   // here 16 means Hexadecimal
    printf("Hexadecimal value = 0x%s\n", buffer);
}

