grammar Elm;

import CommonLexerRules;

/** The start rule; begin parsing here. */
prog:   stat+ ; 

stat:   expr NEWLINE                # printExpr
    |   ID '=' expr NEWLINE         # assign
    |   'clear'                     # clear
    |   NEWLINE                     # blank
    ;

expr:   expr op=('*'|'/') expr         # MulDiv
    |   expr op=('+'|'-') expr         # AddSub
    |   INT                         # int
    |   ID                          # id
    |   '(' expr ')'                # parens
    ;

