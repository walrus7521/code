

ADTs : templatize, may add pairs?
       currently typedef int e_v;
=================================
[ ] binsrch.h
[ ] bitvec.h
[ ] btree.h
[ ] cirque.h
[ ] graph-list.h
[ ] graph-matrix.h
[ ] hash.h
[ ] hash_int.h
[ ] heap.h
[ ] isort.h
[ ] msort.h
[ ] mst.h
[ ] pq. h
[ ] qsort.h
[ ] queue.h
[ ] segtree.h
[ ] slist.h
[ ] string.h
[ ] tree.h
[ ] trie.h
[ ] trie_ints.h

Lists
=====
General list                - list.c
Stacks                      - stack.c
Circular Queues             - cirque.c
Linked Queues               - fifo.c

Trees
============
BSTs                        - tree.c
Balanced BSTs               - tree.c
AVL                         - tree.c
Segmented Tree              - segtree.c

Heaps
=====
Binary Heaps                - heap.c
PQ (max)                    - pqmax.c

Graphs
======
DFS                         - graph.c
BFS                         - graph.c
MST                         - graph.c
Shortest Path               - graph.c
Top Sort                    - graph.c
Transitive Closure (Floyd)  - graph.c (debug)

Sorting
=======
Insertion Sort              - isort.c - arrays
Merge Sort                  - msort.c - lists
Quick Sort                  - qsort.c

Search
======
Binary Search               - binsrch.c (fix this!!)

Hashing
=======
Hash                        - hash.c

Strings
=======
Boyer-Moore                 - string.c
Rabin-Karp                  - string.c
KMP                         - string.c

Multiway Trees
==============
Tries                       - trie.c
B-Trees                     - btree.c

Other
=====
Bit Vectors                 - bitvec.c  

ToDo
====
add transitive_closure(Floyd) to graph.c
add credits
Binary Trees
Generic Trees
Threaded Binary Traversals
Expression Trees
XOR Trees
MISC: Red Black, Splay, Aug, Interval
/*
 *  Add (slist.h): 
 *      slist_get_median(list);
 *      slist_exchange(list, position1, position2);
 *      slist_copy(list1, list2);
 *      slist_join(list1, list2);
 *      slist_split(list, oddlist, evenlist);
 */

