mac: watch.c watch.h test.c
	gcc watch.c test.c -Wall -Os -o test

test: watch.c watch.h test.c
	gcc watch.c test.c -lrt -Wall -Os -o test

clean:
	rm *.exe
