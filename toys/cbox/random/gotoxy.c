#include<stdio.h>
 
//gotoxy() function definition
void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}
 
int main ()
{
    int x=10, y=20;
    gotoxy(x,y); //move cursor position
    printf("Hello World!!!"); //print message
    return 0;
}
