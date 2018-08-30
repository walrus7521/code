#The automatic variable $@ means "the name of the target." The automatic variable $+ means "all prerequisites, space-separated." Automatic variables are pre-defined in Make.

# Definitions
#CC=gcc
CC=g++
#CFLAGS=-g -c -Wall -O0
CFLAGS=-g -c -Wall -O0 -std=gnu++0x
LFLAGS=-o
#OBJS=puma.o SCSIe_ph4_cmds.o parser.o
OBJS=pciu.o
#HEADERS=sdkapi.h sdkapi_oo.h puma.h SCSIe_ph4_cmds.h parser.h
#HEADERS=sdkapi.h sdkapi_oo.h puma.h parser.h

# The default rule - compiling our main program:
all:	pciu
		echo all: make complete

pciu: $(OBJS)
# If we get here, all the dependencies are now built.
# Link it:
	$(CC) -ludev -lusb $(LFLAGS) $@ $+ -Wl,-Map=$@.map

# Tell make how to build .o files from .cpp files:
%.o:%.cpp
	$(CC) $(CFLAGS) $+

#Now make sure that make rebuilds files if included headers change:
$(OBJS): $(HEADERS)

clean:
	rm -f pciu *.o *.map *.gch

