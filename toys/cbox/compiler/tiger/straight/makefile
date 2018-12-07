straight: driver.o util.o straight.o
	cc -g -o straight driver.o straight.o util.o

driver.o: driver.c ../common/util.h
	cc -g -c driver.c

straight.o: straight.c ../common/util.h
	cc -g -c straight.c

util.o: ../common/util.c ../common/util.h
	cc -g -c ../common/util.c

clean: 
	rm -f straight util.o straight.o driver.o
