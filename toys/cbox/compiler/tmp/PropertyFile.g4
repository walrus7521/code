grammar PropertyFile;

top : prop+ ;
prop : ID '=' STRING '\n' ;
ID   : [a-z]+ ;
STRING : '"' .*? '"' ;
