#include "types.h"

/*
    sorting
    search
    ring buffer
    strings
 */

void show(int *a, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d, ", a[i]);
    }
    printf("\n");
}

// each largest element bubbles down to end
void bubble(int *a, int len)
{
    for (int i = 0; i < len; i++) {
        int sorted = 1; // short circuit
        for (int j = 0; j < len-i-1; j++) { // move the bottom
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
    for (int i = 1; i <= len-1; i++) {
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
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (a[i] > a[j]) exchg(a[i], a[j]);
        }
    }
}

uint64_t bitsort(int *a, int len)
{
    uint64_t x = 0;
    for (int i = 0; i < len; i++) {
        x |= (1 << a[i]);
    }
    return x;
}

int is_anagram(char *a, char *b)
{
    char dict[256];
    int len = strlen(a);
    if (len != strlen(b)) return 0;
    for (int i = 0; i < len; i++) dict[i] = 0;
    for (int i = 0; i < len; i++) dict[a[i]]++;
    for (int i = 0; i < len; i++) {
        if (dict[b[i]]-- == 0) return 0;
    }
    return 1;
}

int is_palindrome(char *a)
{
    int len = strlen(a);
    for (int i = 0; i < len/2; i++) {
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
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));

    int a[] = {4,3,1,2,7,31};
    int len = sizeof(a) / sizeof(a[0]);
    show(a, len);
    uint32_t y = bitsort(a, len);
    printf("y: %08x\n", y);
    for (int i = 0; i < 64; i++) {
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
    show(a, len);
    //bubble(a, len);
    //insertion(a, len);
    selection(a, len);
    show(a, len);

    //printf("test bit stuff\n");
    test_bits();
}

