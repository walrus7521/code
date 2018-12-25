%{
#include <stdio.h>
%}

%option noyywrap

%%
"colour"        { printf("color"); }
"flavour"       { printf("flavor"); }
"clever"        { printf("smart"); }
"smart"         { printf("elegant"); }
"conservative"  { printf("liberal"); }
"quit"          { exit(0); }
.               { printf("%s", yytext); }
%%
int main(int argc, char **argv)
{
    yylex();
}
