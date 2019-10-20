CC := clang

CFLAGS := `sdl2-config --cflags --libs` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

HDRS :=

SRCS := game.c

OBJS := $(SRCS:.c=.o)

EXEC := game

all: $(EXEC)

#game: game.c Makefile
#	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# 
#
#first: game.c
#	gcc game.c -I/usr/local/Cellar/sdl2/2.0.10/include -I/usr/local/Cellar/sdl2_image/2.0.10/include -o game
#

clean:
	rm -rf $(EXEC) $(OBJS)

.PHONY: all clean


