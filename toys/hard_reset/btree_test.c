#include "btree2.h"

int main()
{
    BTree *t = BTree_Constructor(3);

    int a[] = {1,3,7,10,11,13,14,15,18,16,19,24,25,26,21,4,5,20,22,2,17,12,6}; 
    int len = sizeof(a) / sizeof(a[0]);
    int i;

    for (i=0; i < len; ++i) {
        BTree_Insert(t, i);
    }
    BTree_Destructor(t);
}
