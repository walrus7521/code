appname := myapp

CXX := clang++
CXXFLAGS := -std=c++11

srcfiles := $(shell find . -name "*.cc")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(appname)

dist-clean: clean
	rm -f *~ .depend

include .depend
