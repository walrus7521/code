CC := g++

CFLAGS := `sdl2-config --cflags --libs` -ggdb3 -O0 --std=c++0x -Wall -lSDL2_image -lm

HDRS :=

SRCS := game.cpp
#SRCS := simple.c
#SRCS := intro.c

OBJS := $(SRCS:.cpp=.o)

EXEC := game

all: $(EXEC)

#game: game.c Makefile
#	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# 
#
#first: game.c
#	gcc game.c -I/usr/local/Cellar/sdl2/2.0.10/include -I/usr/local/Cellar/sdl2_image/2.0.10/include -o game
#

clean:
	rm -rf $(EXEC) $(OBJS)

.PHONY: all clean


