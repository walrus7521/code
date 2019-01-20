grammar Structs3 ;

typeDecl : 'typedef' (fields)+ typeName ';'
         | 'typedef struct' '{' (fields)+ '}' typeName ';'
         | 'typedef union' '{' (fields)+ '}' typeName ';'
         | 'typedef enum' '{' (enum_fields)+ '}' typeName ';'
         ;

typeName : ID ;

fields      : field (',' field)* ';' ;
enum_fields : ID ('=' ID)* (',')* ;

field  : fieldType fieldName ;

fieldType : ID ;
fieldName : ID ;

ID : [a-zA-Z0-9]+ ;
WS : [ \t\n\r]+ -> skip ;
Comment1 : '//' ~[\r\n]* -> skip ;
Comment2 : '#' ~[\r\n]* -> skip ;
INVALID4 : . -> skip ;

