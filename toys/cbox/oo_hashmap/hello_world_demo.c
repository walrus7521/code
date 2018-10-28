// demo of the hashmap 

#include "hashmap.h"
#include <stdio.h>

// with GCC, build by:
// $ gcc hello_world_demo.c hashmap.c -lrt -o hw

int main() {
	hashmap* h = mk_hmap(str_hash_fn, str_eq_fn, str_del_fn);
	
	char* s = (char*) malloc(8);
	char* k = (char*) malloc(8); 
	
	sprintf(s, "hello"); 
	sprintf(k, "world"); 
	
	hmap_add(h, s, k); // map "hello" to "world"
	hmap_add(h, k, s); // map "world" to "hello"
	
	char* x = (char*) hmap_get(h, k);
	printf("%s ", x);
	
	x = (char*) hmap_get(h, s);
	printf("%s!\n", x);
	
	free_hmap(h);
	
	return 0;
}
