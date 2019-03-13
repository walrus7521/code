#include "types.h"

/*
    sorting
    search
    ring buffer
    strings
 */

void show(int *a, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

// each largest element bubbles down to end
void bubble(int *a, int len)
{
    int i, j;
    for (i = 0; i < len; i++) {
        int sorted = 1; // short circuit
        for (j = 0; j < len-i-1; j++) { // move the bottom
            if (a[j] > a[j+1]) {
                sorted = 0;
                exchg(a[j], a[j+1]);
            }
        }
        if (sorted) { // no swaps
            printf("jump out: %d\n", i);
            break;
        }
    }
}

// puts item in correct location each iteration
void insertion(int *a, int len)
{
    int i;
    for (i = 1; i <= len-1; i++) {
        int j = i;
        while (j > 0 && a[j] < a[j-1]) {
            exchg(a[j], a[j-1]);
            j--;
        }
    }
}

// find smallest and exchg with advancing first position
void selection(int *a, int len)
{
    int i, j;
    for (i = 0; i < len; i++) {
        for (j = i; j < len; j++) {
            if (a[i] > a[j]) exchg(a[i], a[j]);
        }
    }
}

// runs in O(n+k)
void counting_sort()
{
    // note: uses 1-based arrays, and no zeros in sorting array.
    int k = 4;
    int n = 5;
    int A[] = {0,4,1,3,4,3};
    int B[n+1];
    int C[k+1]; // no zero in array to be sorted
    int i;

    for (i = 0; i <= k; i++) B[i] = C[i] = 0;
    for (i = 1; i <= n; i++) C[A[i]]++;
    show(C, k+1);
    for (i = 2; i <= k; i++) C[i] += C[i-1]; // prefix sums
    show(C, k+1);
    for (i = n; i >= 1; i--) {
        B[C[A[i]]] = A[i];
        C[A[i]]--;
    }
    show(B, n+1);
}

int digit(int n, int k)
{
   int p = pow(10, k-1);
   int x = n/p;
   int d = x % 10;
   printf("%d digit of %d: p:%d, x:%d is %d\n", k, n, p, x, d);
   return d;
}

void radix_sort()
{
    int A[] = {0,329,457,657,839,436,720,355};
    int num_digits = 3;
    int n = 7;
    int k = 9; // max digit
    int i, j, w;
    int C[k+1]; 
    int B[n+1]; 
    int aux[k+1];
    for (w = 1; w <= num_digits; w++) {
        printf("digit: %d\n", w);
        for (j = 0; j <= k; j++) C[j] = 0;
        // bias digit by 1, so zero is in one's position.
        for (i = 1; i <= 7; i++) C[digit(A[i], w)]++;
        show(C, k+1);
        for (j = 2; j <= k; j++) C[j] += C[j-1];
        show(C, k+1);
        //for (i = 0; i < 7; i++) 
        //  aux[C[digit(a[i], w)]++] = a[i];
        //for (i = 0; i < 7; i++) a[i] = aux[i];
      }
}

uint64_t bitsort(int *a, int len)
{
    int i;
    uint64_t x = 0;
    for (i = 0; i < len; i++) {
        x |= (1 << a[i]);
    }
    return x;
}

int is_anagram(char *a, char *b)
{
    int i;
    char dict[256];
    int len = strlen(a);
    if (len != strlen(b)) return 0;
    for (i = 0; i < len; i++) dict[i] = 0;
    for (i = 0; i < len; i++) dict[a[i]]++;
    for (i = 0; i < len; i++) {
        if (dict[b[i]]-- == 0) return 0;
    }
    return 1;
}

int is_palindrome(char *a)
{
    int i;
    int len = strlen(a);
    for (i = 0; i < len/2; i++) {
        if (a[i] != a[len-i-1]) return 0;
    }
    return 1;
}

int count_bits(uint32_t x)
{
    int count = 0;
    while (x) {
        count++;
        x &= (x-1);
    }
    return count;
}

int parity(uint32_t x)
{
    int count = count_bits(x);
    //return (count % 2) ? 0 : 1; // even parity
    return (count & 0x01); // odd parity
}

void test_bits()
{
    int i;
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));

    int a[] = {4,3,1,2,7,31};
    int len = sizeof(a) / sizeof(a[0]);
    show(a, len);
    uint32_t y = bitsort(a, len);
    printf("y: %08x\n", y);
    for (i = 0; i < 64; i++) {
        if (y & 1) {
            printf("%d\n", i);
        }
        y >>= 1;
    }
}

int main()
{
    //printf("is_ana: %d\n", is_anagram("dude", "eddu"));
    //printf("is_pal: %d\n", is_palindrome("duiud"));
    int a[] = {2,9,1,3,6,4};
    int len = sizeof(a) / sizeof(a[0]);
    //show(a, len);
    //bubble(a, len);
    //insertion(a, len);
    //selection(a, len);
//    counting_sort();
    // unit test digit10(n,k)
    //printf("%d\n", digit(321,3));
    radix_sort();

    //printf("test bit stuff\n");
    //test_bits();
}

