
%option noyywrap yylineno

%{
#include "calc.h"
#include "calc.tab.h"
%}

 /* float exponent */
EXP     ([Ee][-+]?[0-9]+)

%%
 /* single character ops */
"+" |
"-" |
"*" |
"/" |
"=" |
"," |
";" |
"|" |
"(" |
")"     { return yytext[0]; }

 /* comparison ops, all are a CMP token */
">"     { yylval.fn = 1; return CMP; }
"<"     { yylval.fn = 2; return CMP; }
"<>"    { yylval.fn = 3; return CMP; }
"=="    { yylval.fn = 4; return CMP; }
">="    { yylval.fn = 5; return CMP; }
"<="    { yylval.fn = 6; return CMP; }

 /* keywords */
"if"    { return IF; }
"then"  { return THEN; }
"else"  { return ELSE; }
"while" { return WHILE; }
"do"    { return DO; }
"let"   { return LET; }

 /* built-in functions */
"sqrt"  { yylval.fn = B_sqrt;  return FUNC; }
"exp"   { yylval.fn = B_exp;   return FUNC; }
"puma"  { yylval.fn = B_puma;  return FUNC; }
"log"   { yylval.fn = B_log;   return FUNC; }
"print" { yylval.fn = B_print; return FUNC; }

 /* bail out */
"quit" { exit(0); }

 /* names */
[a-zA-Z][a-zA-Z0-9]*    { yylval.s = lookup(yytext); return NAME; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?        { yylval.d = atof(yytext); return NUMBER; }

"//".*
" "
[\t]    { return _EOF; }

\\\n    { printf("c> "); } /* ignore line continuation */

\n      { return EOL; }

"quit"  { exit(1); }

.       { yyerror("mystery char %c\n", *yytext); }


%%


