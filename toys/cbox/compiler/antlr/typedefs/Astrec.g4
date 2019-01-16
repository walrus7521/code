grammar Astrec ;

start       : (decls)*  EOF ;

decls       : (typeDecl)+ (fieldDecl)* (typeDecl)* (attribDecl) ;


typeDecl    : NUM '|' fieldType (fieldName)* ;
fieldDecl   : NUM '|' (fieldType | primType) fieldName ;
attribDecl  : '|' '[' attribs ']' ;



fieldType   : ID ;
primType    : TYPE ;
ptrType     : ID '*' ;
fieldName   : ID ;
attribs     : ID '=' NUM (',' ID '=' NUM)* ;

TYPE    : 'F32'
        | 'U32' | 'U16' | 'U8'
        | 'S32' | 'S16' | 'S8'
        | 'BOOLEAN'
        ;

PTR     : '*' ;
NUM     : [0-9]+ ;
ID      : [a-zA-Z]+[a-zA-Z0-9_]* ;
NL      : '\r'? '\n' ;
WS      : [ \t\r\n]+ -> skip ;
COMMENT : '*' ~[\r\n]* -> skip ;
INVALID : . -> skip ;

