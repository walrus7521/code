
mac: watch.c watch.h WatchState.c StartedState.c StoppedState.c test.c
	gcc watch.c WatchState.c StartedState.c StoppedState.c test.c -Wall -Os -o test

test: watch.c watch.h WatchState.c StartedState.c StoppedState.c test.c
	gcc watch.c WatchState.c StartedState.c StoppedState.c test.c -lrt -Wall -Os -o test

clean:
	rm *.exe
