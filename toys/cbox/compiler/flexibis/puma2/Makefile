puma: lex.yy.c puma.tab.c puma.tab.h
	g++ puma.tab.c lex.yy.c -o puma

puma.tab.c puma.tab.h: puma.y
	bison -d puma.y

lex.yy.c: puma.l puma.tab.h
	flex puma.l

clean:
	rm -rf lex.yy.c puma.tab.c puma.tab.h puma

