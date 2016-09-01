#include <stdio.h>
#include <string.h>

void ftoa(float f,char *buf)
{
    int pos=0,ix,dp,num;
    if (f<0)
    {
        buf[pos++]='-';
        f = -f;
    }
    dp=0;
    while (f>=10.0) 
    {
        f=f/10.0;
        dp++;
    } 
    for (ix=1;ix<8;ix++)
    {
            num = f;
            f=f-num;
            if (num>9)
                buf[pos++]='#';
            else
                buf[pos++]='0'+num;
            if (dp==0) buf[pos++]='.';
            f=f*10.0;
            dp--;
    }
}

int main()
{
    int a = 0xdead;
    float f = 3.14;
    char buffer[20];

    itoa(a, buffer, 2);   // here 2 means binary
    printf("Binary value = %s\n", buffer);
 
    itoa(a, buffer, 10);   // here 10 means decimal
    printf("Decimal value = %s\n", buffer);
 
    itoa(a, buffer, 16);   // here 16 means Hexadecimal
    printf("Hexadecimal value = 0x%s\n", buffer);

    memset(buffer, 0, 20);
    ftoa(f, buffer);
    printf("Float value = %s\n", buffer);

    return 0;
}
