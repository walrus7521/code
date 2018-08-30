p1: lex.yy.o
	gcc -g -o p1 lex.yy.o
lex.yy.o: cal1.l
	flex cal1.l; gcc -g -c lex.yy.c

clean:
	rm -f p1 *.o lex.yy.c

