CXX = g++
CC = g++

all:		students

Student_info.o:	Student_info.cc Student_info.h

grade.o:	grade.cc grade.h median.h Student_info.h

#main3.o:	main3.cc grade.h median.h average.h Student_info.h

students.o:	students.cc median.h Student_info.h

median.o:	median.cc median.h

#average.o:	average.cc average.h

students:		students.o Student_info.o median.o grade.o

test:		all
	./students < data

clean:
	rm -f *.o students

