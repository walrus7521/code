#include <stdio.h>
#include <stdlib.h>

//#define dprintf printf
#define dprintf(...)

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define MAXDIGITS       100
#define PLUS            1
#define MINUS           -1

typedef struct {
    char digits[MAXDIGITS];
    int signbit;
    int lastdigit;
} bignum;

void add_bignum(bignum *a, bignum *b, bignum *c);
void subtract_bignum(bignum *a, bignum *b, bignum *c);
void multiply_bignum(bignum *a, bignum *b, bignum *c);
void divide_bignum(bignum *a, bignum *b, bignum *c);
int compare_bignum(bignum *a, bignum *b);

void print_bignum(bignum *n)
{
    int i;
    if (n->signbit == MINUS) printf("-");
    for (i = n->lastdigit; i >= 0; i--)
        printf("%c", '0'+n->digits[i]);
}

void initialize_bignum(bignum *n)
{
    int i;
    for (i = 0; i < MAXDIGITS; i++) {
        n->digits[i] = (char) 0;
    }
    n->signbit = PLUS;
    n->lastdigit = 0;
}

void int_to_bignum(int s,  bignum *n)
{
    int i, t;
    if (s >= 0) n->signbit = PLUS;
    else n->signbit = MINUS;
    for (i = 0; i < MAXDIGITS; i++) n->digits[i] = (char) 0;
    n->lastdigit = -1;
    t = abs(s);
    while (t > 0) {
        n->lastdigit++;
        n->digits[n->lastdigit] = (t % 10);
        t = t / 10;
    }
    if (s == 0) n->lastdigit = 0;
}

void zero_justify(bignum *n)
{
    while ((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0))
        n->lastdigit--;
    if ((n->lastdigit == 0) && (n->digits[0] == 0))
        n->signbit = PLUS; /* hack to avoid -0 */
}

int compare_bignum(bignum *a, bignum *b)
{
    int i;
    if ((a->signbit == MINUS) && (b->signbit == PLUS)) return (PLUS);
    if ((a->signbit == PLUS)  && (b->signbit == MINUS)) return (MINUS);
    if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
    if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);
    for (i = a->lastdigit; i >= 0; i--) {
        if (a->digits[i] > b->digits[i])
            return (MINUS * a->signbit);
        if (b->digits[i] > a->digits[i])
            return (PLUS * a->signbit);
    }
    return (0);
}

void add_bignum(bignum *a, bignum *b, bignum *c)
{
    int i, carry;
    initialize_bignum(c);
    if (a->signbit == b->signbit) c->signbit = a->signbit;
    else {
        if (a->signbit == MINUS) {
            a->signbit = PLUS;
            subtract_bignum(b, a, c);
            a->signbit = MINUS;
        } else {
            b->signbit = PLUS;
            subtract_bignum(a, b, c);
            b->signbit = MINUS;
        }
        return;
    }
    c->lastdigit = max(a->lastdigit, b->lastdigit)+1;
    carry = 0;
    for (i = 0; i <= c->lastdigit; i++) {
        c->digits[i] = (char) (carry + a->digits[i] + b->digits[i]) % 10;
        carry = (carry + a->digits[i] + b->digits[i]) / 10;
    }
    zero_justify(c);
}

void subtract_bignum(bignum *a, bignum *b, bignum *c)
{
    int borrow, v, i;
    if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
        b->signbit = -1 * b->signbit;
        add_bignum(a, b, c);
        b->signbit = -1 * b->signbit;
        return;
    }
    if (compare_bignum(a, b) == PLUS) {
        subtract_bignum(b, a, c);
        c->signbit = MINUS;
        return;
    }
    c->lastdigit = max(a->lastdigit, b->lastdigit);
    borrow = 0;
    for (i = 0; i <= c->lastdigit; i++) {
        v = (a->digits[i] - borrow - b->digits[i]);
        if (a->digits[i] > 0)
            borrow = 0;
        if (v < 0) {
            v = v + 10;
            borrow = 1;
        }
        c->digits[i] = (char) v % 10;
    }
    zero_justify(c);
}

void digit_shift(bignum *n, int d)
{
    int i;
    if ((n->lastdigit == 0) && (n->digits[0] == 0)) return;
    for (i = n->lastdigit; i >= 0; i--)
        n->digits[i+d] = n->digits[i];
    for (i = 0; i < d; i++) n->digits[i] = 0;
    n->lastdigit = n->lastdigit + d;
}

void multiply_bignum(bignum *a, bignum *b, bignum *c)
{
    bignum row, tmp;
    int i, j;
    initialize_bignum(c);
    row = *a;
    for (i = 0; i <= b->lastdigit; i++) {
        for (j = 1; j <= b->digits[i]; j++) {
            add_bignum(c, &row, &tmp);
            *c = tmp;
        }
        digit_shift(&row, 1);
    }
    c->signbit = a->signbit * b->signbit;
    zero_justify(c);
}

void divide_bignum(bignum *a, bignum *b, bignum *c)
{
    bignum row, tmp;
    int asign, bsign, i, j;
    initialize_bignum(c);
    c->signbit = a->signbit * b->signbit;
    asign = a->signbit;
    bsign = b->signbit;
    a->signbit = PLUS;
    b->signbit = PLUS;
    initialize_bignum(&row);
    initialize_bignum(&tmp);
    c->lastdigit = a->lastdigit;
    for (i = a->lastdigit; i >= 0; i--) {
        digit_shift(&row, 1);
        row.digits[0] = a->digits[i];
        c->digits[i] = 0;
        while (compare_bignum(&row, b) != PLUS) {
            c->digits[i]++;
            subtract_bignum(&row, b, &tmp);
            row = tmp;
        }
    }
    zero_justify(c);
    a->signbit = asign;
    b->signbit = bsign;
}

void reverse_bignum(bignum *a, bignum *b)
{
    int i, j;
    initialize_bignum(b);
    dprintf("reverse: last = %d\n", a->lastdigit);
    for (j = 0, i = a->lastdigit; i >= 0; i--, j++) {
        b->digits[i] = a->digits[j];
    }
    b->lastdigit = a->lastdigit;
    b->signbit = a->signbit;
    zero_justify(b);
}

void copy_bignum(bignum *a, bignum *b)
{
    int i;
    initialize_bignum(b);
    for (i = a->lastdigit; i >= 0; i--) {
        b->digits[i] = a->digits[i];
    }
    b->lastdigit = a->lastdigit;
    b->signbit = a->signbit;
    zero_justify(b);
}

int is_palindrome(bignum *n)
{
    int i, j;
    for (i = 0, j = n->lastdigit; i < n->lastdigit; i++, j--) {
        if (n->digits[i] != n->digits[j]) {
            dprintf("not a palindrome\n");
            return 0;
        }
    }
    dprintf("yes it is a palindrome..\n");
    return 1;
}

int main()
{
    int i, ncases, x, passes;
    bignum a, b, c;

    scanf("%d\n", &ncases);

    for (i = 0; i < ncases; i++) {
        passes = 0;
        initialize_bignum(&a);
        initialize_bignum(&b);
        initialize_bignum(&c);
        scanf("%d\n", &x);
        int_to_bignum(x, &a);
        reverse_bignum(&a, &b);
        do {
            passes++;
            /* printf("a = "); print_bignum(&a); printf("\n"); */
            /* printf("b = "); print_bignum(&a); printf("\n"); */
            add_bignum(&a, &b, &c);
            /* printf("c = "); print_bignum(&c); printf("\n"); */
            copy_bignum(&c, &a);
            reverse_bignum(&a, &b);
        } while (!is_palindrome(&c));
        printf("%d ", passes); print_bignum(&c);
        if (i < ncases-1) printf("\n");
    }
    return 0;
}
