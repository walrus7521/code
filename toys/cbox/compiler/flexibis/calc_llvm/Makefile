calc: lex.yy.c calc.tab.c calc.h calcer.cpp main.cpp
	g++ calcer.cpp main.cpp lex.yy.c calc.tab.c -o calc

lex.yy.c:
	flex calc.l

calc.tab.c:
	bison -d calc.y

clean:
	rm -rf lex.yy.c calc.tab.c calc.tab.h calc
