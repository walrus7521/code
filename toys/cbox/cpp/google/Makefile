CXX = g++
CC = g++

all:		test_database test_composer

#composer.o:	composer.h composer.cc
#	$(CC) $(CFLAGS) -c composer.cc

#database.o:	database.h database.cc
#	$(CC) $(CFLAGS) -c database.cc

test_database:		test_database.o
	$(CC) $(CFLAGS) test_database.cc -o database

test_composer:		test_composer.o
	$(CC) $(CFLAGS) test_composer.cc -o composer

#test:		all
#	./main2 <../data/grades
#	./main3 <../data/grades

clean:
	rm -f *.o database composer

