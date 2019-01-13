CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell /usr/local/opt/llvm/bin/llvm-config --cxxflags)
LDFLAGS=-g $(shell /usr/local/opt/llvm/bin/llvm-config --cxxflags --ldflags core executionengine jit inter preter analysis native bitwriter --system-libs)
LDLIBS=$(shell root-config --libs)

SRCS=kale.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: kale

kale: kale.o
	$(CXX) $(LDFLAGS) -o kale $(OBJS) $(LDLIBS) 

kale.o: kale.cpp

#support.o: support.hh support.cc

clean:
	$(RM) $(OBJS) kale

distclean: clean
	$(RM) kale

