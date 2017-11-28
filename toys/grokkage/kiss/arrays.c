#include "types.h"

/*
    sorting
    search
    ring buffer
    strings
 */

array_t *new()
{
    array_t *a = malloc(sizeof(array_t));
    return a;
}

void show(array_t *a)
{
    for (int i = 0; i < a->size; i++) {
        printf("%d, ", a->a[i]);
    }
    printf("\n");
}

// each largest element bubbles down to end
void bubble(array_t *a)
{
    for (int i = 0; i < a->size; i++) {
        int sorted = 1;
        for (int j = 0; j < a->size-i-1; j++) {
            if (a->a[j] > a->a[j+1]) {
                sorted = 0;
                exchg(a->a[j], a->a[j+1]);
            }
        }
        if (sorted) { // no swaps
            printf("jump out: %d\n", i);
            break;
        }
    }
}

// puts item in correct location each iteration
void insertion(array_t *a)
{
    for (int i = 1; i <= a->size-1; i++) {
        int j = i;
        while (j > 0 && a->a[j] < a->a[j-1]) {
            exchg(a->a[j], a->a[j-1]);
            j--;
        }
    }
}

// find smallest and exchg with advancing first position
void selection(array_t *a)
{
    for (int i = 0; i < a->size; i++) {
        for (int j = i; j < a->size; j++) {
            if (a->a[i] > a->a[j]) exchg(a->a[i], a->a[j]);
        }
    }
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

uint64_t bitsort(array_t *a)
{
    uint64_t x = 0;
    for (int i = 0; i < a->size; i++) {
        x |= (1 << a->a[i]);
    }
    return x;
}

void test_bits()
{
    int x = 0x5a;
    printf("count:  %x => %d\n", x, count_bits(x));
    printf("parity: %x => %d\n", x, parity(x));

    array_t a = {.size=6, {4,3,1,2,7,31}};
    show(&a);
    uint32_t y = bitsort(&a);
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
    printf("is_ana: %d\n", is_anagram("dude", "eddu"));
    printf("is_pal: %d\n", is_palindrome("duiud"));
    array_t a = {.size=6, {2,9,1,3,6,4}};
    //bubble(&a);
    //insertion(&a);
    selection(&a);
    show(&a);

    printf("test bit stuff\n");
    test_bits();
}

