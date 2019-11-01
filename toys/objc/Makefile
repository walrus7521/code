P=mykext
OBJECTS=
INCS=-I/System/Library/Frameworks/Kernel.framework/Headers/
CFLAGS= -g -Wall -O3 -std=c99 $(INCS) mykext.c
LDLIBS=-Xlinker -kext -static -fno-builtin -nostdlib -lkmod
CC=gcc

$(P): $(OBJECTS)

clean:
	rm $(P)

