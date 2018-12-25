/* just like Unix wc */
%{
#include <stdio.h>
int chars = 0;
int words = 0;
int lines = 0;
%}

%option noyywrap

%%
[^ \t\n\r\f\v]+ { words++; chars += strlen(yytext); }
\n        { chars++; lines++; }
.         { chars++; }
%%
int main(int argc, char **argv)
{
    yylex();
    printf("lines: %d, words: %d, chars: %d\n", lines, words, chars);
}

