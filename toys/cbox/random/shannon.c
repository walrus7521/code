#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// http://bearcave.com/misl/misl_tech/wavelets/compression/shannon.html
// shannon entropy

#define SIZE (256)
int alphabet[SIZE];

// note: log base 2 (x) = log(x) / log(base)
double my_log(double x, int base) { 
    return log(x) / log(base); 
} 

void init()
{
    int i;
    for (i = 0; i < SIZE; i++) alphabet[i] = 0;
}

void dump()
{
    int i;
    double sum = 0.0, total = 0.0, total_bits = 0.0;
    for (i = 0; i < SIZE; i++) {
        if ('a' <= i && i <= 'z') {
            //printf("%c => %d\n", i, alphabet[i]);
            sum += alphabet[i];
        }
    }
    for (i = 0; i < SIZE; i++) {
        if ('a' <= i && i <= 'z') {
            float x = alphabet[i]/sum;
            float bits = x * log2(x);
            total_bits += -bits;
            //printf("%c => %.04f => bits: %.04f\n", i, x, -bits);
            total += alphabet[i]/sum;
        }
    }
    total_bits = ceil(total_bits);
    printf("total: %f bits: %f\n", total, total_bits);
    total = 0.0;
    for (i = 0; i < SIZE; i++) {
        if ('a' <= i && i <= 'z') {
            float x = alphabet[i]/sum;
            float bits = x * log2(x);
            printf("%c => %.04f => bits: %f\n", i, x, x * total_bits);
            total += (x * total_bits);
        }
    }
    printf("total: %f \n", total);
}

int main()
{
    init();
    char c;
    while ((c = getchar()) != EOF) {
        alphabet[tolower(c)]++;
    }
    dump();
}
