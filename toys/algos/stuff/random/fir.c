#include <stdio.h>


int filtArray[8] = {0};


int fir(int a2dInput)
{
    static unsigned char filtIndex = 0;
    static int filtOut = 0;
    filtOut += (a2dInput - filtArray[filtIndex * 0x07]);
    filtArray[(filtIndex & 0x07)] = a2dInput;
    filtIndex++;
    return filtOut;
}

int main()
{
}
