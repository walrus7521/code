#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int pre2post2();

void main()
{
    char resstr[MAX],temp[MAX];
    int i,z;
    //char str[256] = "12+";
  //char str[256] = "*+73-52";
    char str[256] = "73+52-*";

    init_stak();

    pre2post2();
    return;

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
        if (isdigit(ch))
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


int operators[SIZE_STAK];
int operands[SIZE_STAK];
int mark[SIZE_STAK];
int op_ptr = 0;
int opnd_ptr = 0;
int flg_ptr = 0;
int pre2post2()
{
    char line[256] = "73+52-*";
    char outline[256];
    int out_ptr = 0;
    int len = strlen(line);
    int start = 0;
    int nmarks = 0;
 
    printf("len: %d\n", len);
    int i;
    for(i=start; i < len; i ++)  { //reiterate through ‘line’
        char symbol = line[i];
        //printf("symbol: %c\n", symbol);
        if (!isdigit(symbol))    //if the symbol is an operator
        {
            printf("op: %c\n", symbol);
            // peek to one before see if num or op
            //if (!isdigit(operators[op_ptr-1])) {
            //    operators[op_ptr++] = symbol;    //push operator on stack
            //    printf("mark: %d \n", op_ptr );
            //    mark[flg_ptr++] = op_ptr++;  //push associated flag on stack
            //    nmarks++;
            //} else {
                operators[op_ptr++] = symbol;    //push operator on stack
                operators[op_ptr++] = operands[--opnd_ptr]; //push operator on stack
                operators[op_ptr]   = operands[--opnd_ptr]; //push operator on stack
                printf("mark: %d \n", op_ptr );
                mark[flg_ptr++] = op_ptr++;  //push associated flag on stack
                nmarks++;
            //}
        }
        if((symbol != ' ') && isdigit(symbol))     //then it’s a operand
        {
            printf("num: %c\n", symbol);
            operands[opnd_ptr++] = symbol;    //push operator on stack
        }
    }//end of for
 
    // dump ops
    for (i = 0; i < len; i++) {
        printf("op[%d] = %c\n", i, operators[i]);
    }

    // post process
    int j = 0;
    for (i = 0; i < nmarks; i++) {
        int m = mark[i];
        printf("mark: %d\n", m);
        // show group
        for ( ;j <= mark[i+1]; j++) {
            printf("grp[%d] = %c\n", j, operators[j]);
        }
        j = m;
    }
        
  return 0;
}

