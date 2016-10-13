#include <stdio.h>
#include <stdlib.h>

#define SIZE_STAK 32
typedef char e_v;
#include "..\phd\stak.inc"

#define MAX 20

struct stack
{
    int top;
    char arr[MAX];
};

void push(struct stack *,char);
char pop(struct stack *);
void prefix_to_postfix(char instr[],char outstr[]);

void main()
{
    char resstr[MAX],temp[MAX];
    int i,z;
    //char str[256] = "12+";
  //char str[256] = "*+73-52";
    char str[256] = "73+52-*";

    init_stak();

    for (i = 0; str[i] != '\0'; i++) ;

    for (i=i-1,z=0; i>=0; z++,i--)
        temp[z]=str[i];

    temp[z] = '\0';
    printf("Prefix string: %s\n", str);
    prefix_to_postfix(str, resstr);
    printf("Postfix string: %s\n", resstr);
}

// broken
void prefix_to_postfix(char instr[],char outstr[])
{
    int i,j,ct=1,z=0;
    char ch,opnd1,opnd2;
    for (i = 0; instr[i] != '\0'; i++) {
        ch=instr[i];
        //printf("str[%d] = %c\n", i, ch);
        if(isdigit(ch))
        {
            printf("isdigit: %c\n", ch);
            stkpush(ch);
        }
        else
        {
            //printf("isop: %c ct %d\n", ch, ct);
            if(ct==1)
            {
                opnd1 = stkpop();
                opnd2 = stkpop();
                printf("op1: %c %c %c\n", ch, opnd1, opnd2);

                outstr[z++]=opnd1;
                outstr[z++]=opnd2;
                outstr[z++]=ch;
                ct++;
            }
            else
            {
                opnd2 = stkpop();
                printf("op2: %c %c\n", ch, opnd2);
                outstr[z++]=opnd2;
                outstr[z++]=ch;
            }
        }
    }
    outstr[z]='\0';
}


