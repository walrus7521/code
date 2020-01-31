#include "sedgewick.h"

int main()
{
    int n=0, i; //, a[MAXN+1];
    //while (scanf("%d", &a[n]) != EOF) n++;
    int a[] = {'a','s','o','r','t','i','n','g','e','x','a','m','p','l','e'};
    int p[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    int k[] = {1,73,25,87,42,54,66,28};

    n = 15;
    //selsort(a, n);
    //inssort(a, n);
    //bubsort(a, n);
    //bubsort(a, n);
    //radix_exchange_sort(a, 1, 14, 30);
    //for (i = 0; i < n; i++) printf("%c ", a[i]);
    //indirect_sort(a, p, n); for (i = 0; i < n; i++) printf("%c ", a[p[i]]);
    //printf("\n");

    //int select = 1;
    //select_kth_largest(k, 0, 7, select);
    //printf("k[select] = %d\n", k[select]);

    three_way_merge_sort();

}
