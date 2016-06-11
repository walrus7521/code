CXX = g++
CC = g++

all:		main2 main3

Student_info.o:	Student_info.cc Student_info.h

grade.o:	grade.cc grade.h median.h average.h Student_info.h

main3.o:	main3.cc grade.h median.h average.h Student_info.h

median.o:	median.cc median.h

average.o:	average.cc average.h

main3:		main3.o grade.o median.o average.o Student_info.o

test:		all
	./main2 <../data/grades
	./main3 <../data/grades

clobber:
	rm -f *.o *.exe core main2 main3

