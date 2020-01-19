libfoo.so: foo.o
	g++ -shared -o libfoo.so foo.o

foo.o: foo.cpp
	g++ -c foo.cpp

clean:
	rm -rf foo.o libfoo.so

