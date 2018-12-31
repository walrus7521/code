CFLAGS=-g -Os 

TARGETS	= recur

all:	$(TARGETS)

lockstat: recur.c
	${CC} ${CFLAGS} -o $@ $?
clean:
	rm -rf $(TARGETS)
