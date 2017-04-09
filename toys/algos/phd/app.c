/* outline of app
 * database of lists of tasks
 *    id : list id
 *    priority : order
 *    data due : meta data
 *    predecessors & successors
 *    store in json - ser/des
 *    cli
 */ 

#include <stdio.h>
#define _NO_MAIN_
#include "hash.c"
#include "graph.c"
#include "heap.c"
//#include "list.c"
#include "seasort.c"
//#include "tasks.c"
//#include "tree.c"
#include "trie.c"

int main()
{
    //test_hash();
    //test_graph();
    //test_heap();
    //test_list();
    test_seasort();
    //test_tasks();  conflicts
    //test_tree();
    //test_trie();
}

