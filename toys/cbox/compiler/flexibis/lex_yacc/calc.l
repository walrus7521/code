%{
// calc.l -- a simple calculator program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.tab.h"
extern YYSTYPE yylval;

%}
delim         [ \t]
whitesp       {delim}+
digit         [0-9]
number        [-]?{digit}*[.]?{digit}+
%%
{number}  { sscanf(yytext, "%lf", &yylval); return NUMBER;}
"+"       { return PLUS; }
"-"       { return MINUS; }
"/"       { return SLASH; }
"*"       { return ASTERISK; }
"("       { return LPAREN; }
")"       { return RPAREN; }
"\n"      { return NEWLINE; }
{whitesp} { /* No action and no return */}

