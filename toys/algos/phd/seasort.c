#include <stdio.h>
#include <string.h>


#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exchg(A, B) { int t = A; A = B; B = t; } 
#define cmpexchg(A, B) if (less(B, A)) exchg(A, B)

void show(int a[], int n)
{
    int i;
    for (i = 0 ; i < n; i++) {
        printf("%3d", a[i]);
    }
    printf("\n\n\n ");
}

int boyer(char *haystack, char *needle, int start)
{
    int hlen = strlen(haystack);
    int nlen = strlen(needle);
    int jump, offset = start;
    int scan = 0;
    int last = nlen - 1;
    int skip[256] = {0};

    if( nlen <= 0 || hlen <= 0 )
        return -1;
    
    for(scan = 0; scan < last; scan++) {
        skip[ needle[ scan ] ] = last - scan;
    }

    while( hlen >= nlen ) {
        for( scan = last; haystack[ offset + scan ] == needle[ scan ]; scan-- ) {
            if( scan == 0 ) { return offset; }
        }
        jump = skip[ haystack[ offset + last ] ];
        jump = (jump != 0) ? jump : nlen;
        hlen -= jump;
        offset += jump;
    }

    return -1;
}

int match(char *string, char *pattern)
/*
 * return position of the 1st occurence of pattern p
 * in the string, and -1 if not found.
 */
{
    int i, j;
    int plen, tlen;

    plen = strlen(pattern);
    tlen = strlen(string);

    for (i = 0; i <= (tlen-plen); ++i) {
        j = 0;
        while ((j < plen) && (string[i+j] == pattern[j]))
            ++j;
        if (j == plen) return (i);
    }
    return (-1);
}

int palindrome(char *s)
{
    int len = strlen(s);
    int n = len-1;
    int i;
    for (i = 0; i < len/2; i++, n--) {
        if (s[i] != s[n]) {
            return 0;
        }
    }
    return 1;
}

int anagram(char *s1, int len1, char *s2, int len2)
{
    int ascii[256];
    int i;
    if (len1 != len2) {
        return 0;
    }
    for (i = 0; i < 256; i++) ascii[i] = 0;
    for (i = 0; i < len1; i++) ascii[s1[i]]++;
    for (i = 0; i < len1; i++) {
        if (ascii[s2[i]]-- == 0) {
            return 0;
        }
    }
    for (i = 0; i < 256; i++) {
        if (ascii[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int sequential_search(char *s, int n, char k)
{
    int i = 0;
    while (i < n && s[i] != k) i++;
    if (i < n) return i;
    return -1;
}

int binsearch(char *s, int n, char k)
{
/*
 * binary search of array s of size n
 * for the value k.
 */
    int low, high, mid;
    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if (k > s[mid]) low = mid + 1;
        else if (k < s[mid]) high = mid - 1;
        else return k;
    }
    return -1;
}

int partition(int *A, int lo, int hi) {
    int i, p, firsthigh;
    p = hi; /* pick a partition (=hi) */
    firsthigh = lo; /* firsthigh is the partition boundary */
    for (i = lo; i < hi; ++i) {
        if (A[i] < A[p]) {
            exchg(A[i], A[firsthigh]);
            firsthigh++;
        }
    }
    exchg(A[p], A[firsthigh]);
    return firsthigh;
}

void quicksort(int *A, int lo, int hi) {
    int p;
    if (lo < hi) {
        p = partition(A, lo, hi);
        quicksort(A, lo, p-1);
        quicksort(A, p+1, hi);
    }
}

void selection(int a[], int n)
{
    int i, j, min;
    for (i = 0 ; i <= (n - 2) ; i++) {
        min = i;
        // Find the smallest element
        for ( j = i + 1 ; j <= n-1 ; j++ ) {
            if ( a[j] < a[min] )
                min = j; 
        }
        exchg(a[i], a[min]);
    }
}

void insertion(int a[], int n)
{
    int c, d, temp;
    for (c = 1 ; c <= n - 1; c++) { 
        d = c;
        while ( d > 0 && a[d] < a[d-1]) { 
            exchg(a[d], a[d-1]);
            d--; 
        }
    }
}

void bubble(int a[], int n)
{
    int i, d, pos;
    for (i = 0; i < (n-1); i++) {
        pos = i;
        for (d = i+1; d < n; d++) {
            if (a[pos] > a[d]) pos = d;
        }
        if (pos != i) {
            exchg(a[i], a[pos]);
        } 
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2; // partition
 
        // Sort first and second halves
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

void test_strings()
{

    int f;
    char data[]  = "sledbobber\0";
    char data2[] = "sleddels";
    char data3[] = "abbcz";
    char data4[] = "ycabb";
    char patt[]  = "bbe";
    
    //f = match("bob", data);
    //if (f != -1) printf("found match at %d -> %s\n", f, &data[f]);

    printf("is match %d\n", match(data, "bob"));
    printf("is pal   %d\n", palindrome(data2));
    printf("is ana   %d\n", anagram(data3, strlen(data3), data4, strlen(data4)));
    printf("sequential search %d\n", sequential_search(data, 10, 'd'));
    printf("binsearch %c\n", binsearch(data3, 5, 'c'));
    printf("boyer %d\n", boyer(data, patt, 0));

}

void test_sort()
{
    int a[] = {26,33,35,29,19,12,22,15,42,69,1};
    int sz = sizeof(a)/sizeof(a[0]);
    show(a, sz);
    //selection(a, sz);
    //printf("bubble: "); bubble(a, sz);
    //printf("insertion: "); insertion(a, sz);
    printf("merge sort: "); merge_sort(a, 0, sz-1);
    //printf("quicksort: "); quicksort(a, 0, sz-1);
    show(a, sz);
    //printf("binsearch %d\n", binsearch(42, a, sz));
  
}

int main() {
    test_strings();
    //test_sort();
  
    return 0;
}
