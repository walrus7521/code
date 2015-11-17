#include <stdio.h>    


int main()
{
    char a[]={'a','b','c','d'}; 
    char b[]={'c','d','e','f'}; 
    int s[256], i;
    // for considering all ascii values, serves as a hash function 
    for(i=0; i < 256; i++) 
        s[i] = 0; 

    for (i = 0; i < sizeof(a); i++) { 
        s[a[i]]++; 
    } 

    for(i = 0; i < sizeof(b); i++) { 
        if (s[b[i]] > 0) 
            printf("b[%d] = %c\n", i, b[i]);
    } 
    //complexity O(m+n); m- length of array a n- length of array b
    return 0;
}
