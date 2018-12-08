tree: driver.o util.o
	cc -g -o tree driver.o util.o

driver.o: driver.c ../common/util.h
	cc -g -c driver.c

util.o: ../common/util.c ../common/util.h
	cc -g -c ../common/util.c

clean: 
	rm -f tree util.o driver.o
