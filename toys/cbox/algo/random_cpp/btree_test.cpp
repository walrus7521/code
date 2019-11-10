#include <iostream>
#include <cstdio>
#include "btree.hpp"

// Driver program to test btrees
// g++ -std=c++0x btree.c btree_test.cpp
//

int main() 
{ 
    BTree t(3); // A B-Tree with minium degree 3 
  
    int a[] = {1,3,7,10,11,13,14,15,18,16,19,24,25,26,21,4,5,20,22,2,17,12,6}; 
    int len = sizeof(a) / sizeof(a[0]);

    for (auto i : a) {
        //printf("%d\n", i);
        t.insert(i);
    }
    for (auto i : a) {
        printf("remove: %d\n", i);
        t.remove(i);
        t.traverse(); 
    }
    
    return 0;
} 

