#include <stdio.h>

/*
 * odd parity is 1, even parity is 0
 */
short Parity1(unsigned long long x)
{
    short parity = 0;
    while (x) {
        parity ^= (x & 1);
        x >>= 1;
    }
    return parity;
}

short Parity2(unsigned long long x)
{
    short parity = 0;
    while (x) {
        parity ^= 1;
        x &= (x - 1); // drops lowest set bit
    }
    return parity;
}

                                   /* (4-bit, see kWordSize) bit counts for 0..F */
                                   /* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
unsigned int precomputed_parity[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
short Parity3(unsigned long long x)
{
    unsigned short xor_sum, bit_count, parity;
    int index0, index1, index2, index3;
    int index4, index5, index6, index7;
    int index8, index9, indexA, indexB;
    int indexC, indexD, indexE, indexF;
    const unsigned int kWordSize = 4;
    const unsigned int kBitMask = 0xF;

    /* shift counts:
     * 0 => 60
     * 1 => 56
     * 2 => 52
     * 3 => 48
     * 4 => 44
     * 5 => 40
     * 6 => 36
     * 7 => 32
     * 8 => 28
     * 9 => 24
     * A => 20
     * B => 16
     * C => 12
     * D => 8
     * E => 4
     * F => 0
     */
    
    index0 = (x >> (15 * kWordSize) & kBitMask);
    index1 = (x >> (14 * kWordSize) & kBitMask);
    index2 = (x >> (13 * kWordSize) & kBitMask);
    index3 = (x >> (12 * kWordSize) & kBitMask);
    index4 = (x >> (11 * kWordSize) & kBitMask);
    index5 = (x >> (10 * kWordSize) & kBitMask);
    index6 = (x >> ( 9 * kWordSize) & kBitMask);
    index7 = (x >> ( 8 * kWordSize) & kBitMask);
    index8 = (x >> ( 7 * kWordSize) & kBitMask);
    index9 = (x >> ( 6 * kWordSize) & kBitMask);
    indexA = (x >> ( 5 * kWordSize) & kBitMask);
    indexB = (x >> ( 4 * kWordSize) & kBitMask);
    indexC = (x >> ( 3 * kWordSize) & kBitMask);
    indexD = (x >> ( 2 * kWordSize) & kBitMask);
    indexE = (x >> ( 1 * kWordSize) & kBitMask);
    indexF = (x                     & kBitMask);

    printf("x     : 0x%llx\n", x);
    printf("index0: %x => %x\n", index0, precomputed_parity[index0]);
    printf("index1: %x => %x\n", index1, precomputed_parity[index1]);
    printf("index2: %x => %x\n", index2, precomputed_parity[index2]);
    printf("index3: %x => %x\n", index3, precomputed_parity[index3]);
    printf("index4: %x => %x\n", index4, precomputed_parity[index4]);
    printf("index5: %x => %x\n", index5, precomputed_parity[index5]);
    printf("index6: %x => %x\n", index6, precomputed_parity[index6]);
    printf("index7: %x => %x\n", index7, precomputed_parity[index7]);
    printf("index8: %x => %x\n", index8, precomputed_parity[index8]);
    printf("index9: %x => %x\n", index9, precomputed_parity[index9]);
    printf("indexA: %x => %x\n", indexA, precomputed_parity[indexA]);
    printf("indexB: %x => %x\n", indexB, precomputed_parity[indexB]);
    printf("indexC: %x => %x\n", indexC, precomputed_parity[indexC]);
    printf("indexD: %x => %x\n", indexD, precomputed_parity[indexD]);
    printf("indexE: %x => %x\n", indexE, precomputed_parity[indexE]);
    printf("indexF: %x => %x\n", indexF, precomputed_parity[indexF]);

    xor_sum = (precomputed_parity[index0] ^
               precomputed_parity[index1] ^
               precomputed_parity[index2] ^
               precomputed_parity[index3] ^
               precomputed_parity[index4] ^
               precomputed_parity[index5] ^
               precomputed_parity[index6] ^
               precomputed_parity[index7] ^
               precomputed_parity[index8] ^
               precomputed_parity[index9] ^
               precomputed_parity[indexA] ^
               precomputed_parity[indexB] ^
               precomputed_parity[indexC] ^
               precomputed_parity[indexD] ^
               precomputed_parity[indexE] ^
               precomputed_parity[indexF] );

    bit_count = (precomputed_parity[index0] +
                 precomputed_parity[index1] +
                 precomputed_parity[index2] +
                 precomputed_parity[index3] +
                 precomputed_parity[index4] +
                 precomputed_parity[index5] +
                 precomputed_parity[index6] +
                 precomputed_parity[index7] +
                 precomputed_parity[index8] +
                 precomputed_parity[index9] +
                 precomputed_parity[indexA] +
                 precomputed_parity[indexB] +
                 precomputed_parity[indexC] +
                 precomputed_parity[indexD] +
                 precomputed_parity[indexE] +
                 precomputed_parity[indexF] );

    parity = xor_sum & 1;
    printf("bit_count:  %d\n", bit_count);
    printf("xor      :  %d\n", xor_sum);
    printf("parity   :  %d\n", parity);
               
    return parity;
}

const int kFourBitParityLookupTable = 0x6996;
short FourBitParityLookup(int x) {
    return kFourBitParityLookupTable >> x;
}
short Parity4(unsigned long long x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >>  8;
    x ^= x >>  4;
    x &= 0xf;
    return FourBitParityLookup(x) & 1;
}

/* this works
 * http://stackoverflow.com/questions/9133279/bitparity-finding-odd-number-of-bits-in-an-integer
 */
short Parity5(unsigned long long x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x1;
    return x;
}

void dump_parity()
{
    int i;
    for (i = 0; i < 16; i++) {
        printf("[%d] = %u\n", i, precomputed_parity[i]);
    }
}

void test()
{
    int t, x = 0xc10;
    int parity = 0;
    t = x;
    while (x) {
        printf("x = %x\n", x);
        parity ^= 1;
        x &= (x - 1); // drops lowest set bit
    }
    printf("parity of %x is %x\n", t, parity);
}

int main()
{
//    unsigned long long x = 0x3, running = 0;
//    for (x = 0; x < 14; x++) {
//        printf("parity of: %x is %x\n", x, Parity3(x));
//        running ^= Parity3(x);
//    }
//    printf("running parity: %x\n", running);
    //dump_parity();
    printf("parity1 = %x\n", Parity1(0xabce123422334543));
    printf("parity2 = %x\n", Parity2(0xabce123422334543));
    printf("parity3 = %x\n", Parity3(0xabce123422334543));
    printf("parity4 = %x\n", Parity4(0xabce123422334543));
    printf("parity5 = %x\n", Parity5(0xabce123422334543));
    //test();
    return 0;
}
