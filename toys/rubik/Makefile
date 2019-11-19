CC=gcc
RM=rm -f
CFLAGS=-g -Wall -Os
LDFLAGS=-g

SRCS=list.c tree.c test.c
OBJS=$(subst .c,.o,$(SRCS))

all: test

test: list.o tree.o test.o
	$(CC) $(LDFLAGS) -o test $(OBJS)

test.o: test.c

clean:
	$(RM) $(OBJS) test
