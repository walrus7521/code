calc: lex.yy.c calc.tab.c
	gcc lex.yy.c calc.tab.c -o calc

lex.yy.c:
	flex calc.l

calc.tab.c:
	bison calc.y

clean:
	rm -rf lex.yy.c calc.tab.c calc.tab.h calc
