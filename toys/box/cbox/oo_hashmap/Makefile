test2: hashmap.c hashmap.h hello_world_demo.c
	gcc hashmap.c hello_world_demo.c -Wall -Os -o test

test: hashmap.c hashmap.h hello_world_demo.c
	gcc hashmap.c hello_world_demo.c -lrt -Wall -Os -o test

static: hashmap.c
	gcc -O3 -lrt -c hashmap.c

shared: hashmap.c hashmap.h
	gcc -fPIC -shared -Wl,-soname,libhashmap.so -lc -O3 -lrt -o libhashmap.so hashmap.c
#gcc -fPIC -shared -Wl,-soname,libhashmap.so -lc -O3 -lrt -o libhashmap.so hashmap.c
