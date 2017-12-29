 

http://aquamentus.com/flex_bison.html
http://dinosaur.compilertools.net/bison/bison_5.html


flex snork.l 
# on mac
g++ lex.yy.c -ll -o snork
# on linux
g++ lex.yy.c -lfl -o snork

% bison -d snork.y
% flex snork.l
% g++ snork.tab.c lex.yy.c -ll -o snork
% ./snork

make snork

> forcing carriage returns


