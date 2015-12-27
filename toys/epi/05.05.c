#include <stdio.h>
#include <inttypes.h>

/*
 * Compute x * y without multiply or add
 *
 * Write a function that multiplies 2 nonnegative integers.  The
 * only operators you are allowed to use are assignment and bitwise
 * operators, ie, >>, <<, |, &, ~, ^.  (You cannot use increment
 * or decrement).  You may use loops, conditionals and functions
 * you write yourself.
 *
 */


/*
 * To add, we mimick the grade school algorithm for addition. This consists 
 * computing the sum bit-by-bit, and "rippling" the carry along. We use a 
 * bitmask that we use to identify the k-th bit in x, and to test whether 
 * all bits have been read.
 *
 */

uint64_t add2(uint64_t x, uint64_t y)
{
    uint64_t a, b, cin, cout, and1, and2, and3, sum, i, one;
    sum = cin = cout = 0;
    one = 1;
    for (i = 0; i < 64; i++) {
        if (x==0 && y == 0) break;
        a = (x & one);
        b = (y & one);
        sum |= a ^ b;
        sum ^= cin;// & (one << i);
        and1 = a & cin; //& (one << i);
        and2 = a & cin; //& (one << i);
        and3 = a & b;
        cout = and1 | and2 | and3;
        cin |= cout;
        printf("[%lld]: a:%llx, b:%llx, and1:%llx, and2:%llx, and3:%llx, sum:%llx, cout:%llx\n", 
                i, a, b, and1, and2, and3, sum, cout);
        x >>= one; y >>= one;
    }
    return sum;
}

uint64_t add3(uint64_t a, uint64_t b)
{
    uint64_t sum=0, cin=0, k = 1, temp_a=a, temp_b=b, one=1;
    while (temp_a || temp_b) {
        uint64_t ak = a & k, bk = b & k;
        uint64_t cout = (ak & bk) | (ak & cin) | (bk & cin);
        sum |= (ak ^ bk ^ cin);
        cin = cout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;

    }
    return sum | cin;
}

/* the solution is to mimick the grade school algorithm for multiplication.
 * Suppose we are to multiply x and y.  We initialize s to 0 and iterate
 * through the bits of x, adding (2^k)*y to s if x is 1.  The value (2^k)*y 
 * can be computed by left-shifting y by k. 
 */
uint64_t multiply(uint64_t x, uint64_t y)
{
    uint64_t sum = 0;
    while (x) {
        if (x & 1) {
            sum = add3(sum, y);
        }
        x >>= 1;
        y <<= 1;
    }
    printf("%llx = %llx x %llx\n", sum, x, y);
    return sum;
}

int main()
{
    uint64_t x, y;

    x = 0x11;
    y = 0x12;
    printf("add %lld + %lld = %lld => truth=%lld\n", x, y, add3(x, y), x+y);
    printf("multiply %lld X %lld = %lld => truth=%lld\n", x, y, multiply(x, y), x*y);
}
