CXX = g++
CC = g++

all:		test_database

composer.o:	composer.h composer.cc
	$(CC) $(CFLAGS) -c composer.cc

database.o:	database.h database.cc
	$(CC) $(CFLAGS) -c database.cc

test_database:		test_database.o composer.o database.o
	$(CC) $(CFLAGS) composer.o database.o test_database.cc -o database

#test:		all
#	./main2 <../data/grades
#	./main3 <../data/grades

clean:
	rm -f *.o test_database

