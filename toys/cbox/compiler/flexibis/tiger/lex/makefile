lextest: driver.o lex.yy.o errormsg.o util.o
	cc -g -o lextest driver.o lex.yy.o errormsg.o util.o

driver.o: driver.c tokens.h errormsg.h ../common/util.h
	cc -g -c driver.c

errormsg.o: errormsg.c errormsg.h ../common/util.h
	cc -g -c errormsg.c

lex.yy.o: lex.yy.c tokens.h errormsg.h ../common/util.h
	cc -g -c lex.yy.c

lex.yy.c: tiger.lex
	lex tiger.lex

util.o: ../common/util.c ../common/util.h
	cc -g -c ../common/util.c

clean: 
	rm -f lextest util.o driver.o lex.yy.o lex.yy.c errormsg.o
