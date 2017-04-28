# Makefile template for shared library

#CC = g++ -std=c++14 # C compiler
CXX=g++ -std=c++14
# unused CPPFLAGS -dynamiclib -flat_namespace
CPPFLAGS = -fPIC -Wall -Wextra -O2 -g # CPP flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libmx.so # target lib

SRCS = mxapp.cpp # src1.c src2.c # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CXX) ${LDFLAGS} -o $@ $^

$(SRCS:.cpp):%.cpp
	$(CXX) $(CPPFLAGS) -MM $< >$@

#include $(SRCS:.cpp=.)

#.PHONY: clean
clean:
	${RM} ${TARGET_LIB} ${OBJS}
