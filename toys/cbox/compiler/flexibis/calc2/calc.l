
%option noyywrap

%{
#include "calc.h"
#include "calc.tab.h"
%}

 /* float exponent */
EXP     ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")"     { return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

"quit"  { exit(1); }

\n      {return EOL; }
"//".*
[ \t]   { /* ignore whitespace */ }
.       { yyerror("mystery char %c\n", *yytext); }


%%
