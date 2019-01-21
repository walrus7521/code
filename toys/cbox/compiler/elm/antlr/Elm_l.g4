grammar Elm;

import CommonLexerRules;

/** The start rule; begin parsing here. */
prog:   stat+ ; 

stat:   expr NEWLINE                
    |   ID '=' expr NEWLINE         
    |   'clear'                     
    |   NEWLINE                     
    ;

expr:   expr op=('*'|'/') expr     
    |   expr op=('+'|'-') expr      
    |   INT                         
    |   ID                          
    |   '(' expr ')'                
    ;

