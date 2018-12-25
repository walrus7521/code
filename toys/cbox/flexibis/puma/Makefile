all: puma

puma.tab.c puma.tab.h:	puma.y
	bison -d puma.y

lex.yy.c: puma.l puma.tab.h
	flex puma.l

puma: lex.yy.c puma.tab.c puma.tab.h
	gcc -o puma puma.tab.c lex.yy.c

clean:
	rm puma puma.tab.c lex.yy.c puma.tab.h
