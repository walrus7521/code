grammar Structs ;

typeDeclaration : 'typedef struct' '{' (method)* '}' typeName ';' ;
typeName : ID ;
method : methodName '{' (instruction)+ '}' ;
methodName : ID ;
instruction : ID ;

ID : [a-zA-Z0-9]+ ;
WS : [ \t\n\r]+ -> skip ;

