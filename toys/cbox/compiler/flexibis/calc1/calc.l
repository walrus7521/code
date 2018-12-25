%{
#include <stdio.h>
#include <stdlib.h>

enum yytokentype {
    NUMBER = 258,
    ADD = 259,
    SUB = 260,
    MUL = 261,
    DIV = 262,
    ABS = 263,
    OP  = 264,
    CP  = 265,
    EOL = 266
};
int yylval;
%}

%option noyywrap

%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"|"     { return ABS; }
"("     { return OP;  }
")"     { return CP;  }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
0x[a-f0-9]+  { char *pend; yylval = strtol(yytext,&pend,16); return NUMBER; }
\n      { return EOL; }
[ \t]   {}
.       { printf("mystery char %c\n", *yytext); }

%%

#if 0
int main(int argc, char **argv)
{
    int tok;

    while ((tok = yylex()) != 0) {
        printf("%d", tok);
        if (tok == NUMBER) printf(" = %d\n", yylval);
        else printf("\n");
    }
}
#endif

