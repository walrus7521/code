
%{
#include <cstdio>
#include "snazzle.tab.h" // token types from Bison
int linenum = 0;
%}

%option noyywrap

%%
sNaZZle         { return SNAZZLE; }
type            { return TYPE; }
end             { return END; }
[ \t]           ; // semicolen means skip whitespace
[ \r?\n]        { linenum++; }
[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+          { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+    { 
        yylval.sval = strdup(yytext);
        return STRING;
}
.               ; // skip everything else
%%

#if 0 // moved to bison
int main(int argc, char *argv[]) {
    // lex through the input:
    FILE *myfile;
    yyin = stdin;
    if (argc > 1) {
        myfile = fopen(argv[1], "r");
        yyin = myfile;
    }
    while (yylex());
    cout << linenum << endl;
}
#endif

