snork.tab.c snork.tab.h: snork.y
	bison -d snork.y

lex.yy.c: snork.l snork.tab.h
	flex snork.l

snork: lex.yy.c snork.tab.c snork.tab.h
	g++ snork.tab.c lex.yy.c -ll -o snork
   
clean:
	rm -rf snork.tab.c snork.tab.h lex.yy.c snork

