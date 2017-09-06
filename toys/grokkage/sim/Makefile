all: shell.cc
	g++ -std=c++0x shell.cc bus.c ios.c dev.c hal.c ifs.c -lrt -Wall -Os -o shell
#mac: dsim.c
#	gcc sim.c -Wall -Os -o dsim

clean:
	rm *.exe
