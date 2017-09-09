# https://www.gnu.org/software/make/manual/make.html

CPP=g++ -std=c++0x
CC=gcc
CFLAGS=-c -Wall
#LDFLAGS=-lrt -Os
LDFLAGS=-Os

SOURCES=shell.cc bus.c ios.c dev.c hal.c ifs.c
OBJECTS=$(SOURCES:.cpp=.o .c=.o)
EXECUTABLE=shell

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CPP) $(CFLAGS) $< -o $@
	
.c.o:
	$(CPP) $(CFLAGS) $< -o $@

#all: shell

#shell: shell.o bus.o ios.o dev.o hal.o ifs.o
#	$(CPP) shell.o bus.o ios.o dev.o hal.o ifs.o -lrt -Os -o shell

#shell.o: shell.cc
#	$(CPP) $(CFLAGS) shell.cc

#bus.o: bus.c
#	$(CPP) $(CFLAGS) bus.c

#ios.o: ios.c
#	$(CPP) $(CFLAGS) ios.c

#dev.o: dev.c
#	$(CPP) $(CFLAGS) dev.c

#hal.o: hal.c
#	$(CPP) $(CFLAGS) hal.c

#ifs.o: ifs.c
#	$(CPP) $(CFLAGS) ifs.c


clean:
	rm *o *exe
