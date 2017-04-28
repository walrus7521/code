#include <stdio.h>
#include <inttypes.h>

/*
 * reverse bits
 *
 *  write code that takes 64-bit integer and returns the reversal of the integer bits
 */
unsigned long long reverse(uint64_t x) {
    uint64_t y = x, bi, bj, mi, mj;
    int i, j;
    i = 0; j = 63;
    while (i < 32) {
        mi = 1ULL << i;
        mj = 1ULL << j;
        bi = x & mi;
        bj = x & mj;
        if ((bi>>i) != (bj>>j)) {
            /* swap bits (i, j) */
            y ^= ((mi) | (mj));
        }
        i++;
        j--;
    }
    return y;
}


/* lookup tables
 */
/* (4-bit (kWordSize) bit reversals 0..F */
               /* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
uint64_t precomputed_bit_reversal[] = { 
    /* 0x0, */ 0x0,
    /* 0x1, */ 0x8,
    /* 0x2, */ 0x4,
    /* 0x3, */ 0xC,
    /* 0x4, */ 0x2,
    /* 0x5, */ 0xA,
    /* 0x6, */ 0x6,
    /* 0x7, */ 0xE,
    /* 0x8, */ 0x1,
    /* 0x9, */ 0x9,
    /* 0xA, */ 0x5,
    /* 0xB, */ 0xD,
    /* 0xC, */ 0x3,
    /* 0xD, */ 0xB,
    /* 0xE, */ 0x7,
    /* 0xF, */ 0xF
};

uint64_t reverse_lut(uint64_t x)
{
    uint64_t or_sum;
    int index0, index1, index2, index3;
    int index4, index5, index6, index7;
    int index8, index9, indexA, indexB;
    int indexC, indexD, indexE, indexF;

    int shift0, shift1, shift2, shift3;
    int shift4, shift5, shift6, shift7;
    int shift8, shift9, shiftA, shiftB;
    int shiftC, shiftD, shiftE, shiftF;
    
    uint64_t val0, val1, val2, val3;
    uint64_t val4, val5, val6, val7;
    uint64_t val8, val9, valA, valB;
    uint64_t valC, valD, valE, valF;

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
    
    index0 = (x >> ( 0 * kWordSize) & kBitMask);
    index1 = (x >> ( 1 * kWordSize) & kBitMask);
    index2 = (x >> ( 2 * kWordSize) & kBitMask);
    index3 = (x >> ( 3 * kWordSize) & kBitMask);
    index4 = (x >> ( 4 * kWordSize) & kBitMask);
    index5 = (x >> ( 5 * kWordSize) & kBitMask);
    index6 = (x >> ( 6 * kWordSize) & kBitMask);
    index7 = (x >> ( 7 * kWordSize) & kBitMask);
    index8 = (x >> ( 8 * kWordSize) & kBitMask);
    index9 = (x >> ( 9 * kWordSize) & kBitMask);
    indexA = (x >> (10 * kWordSize) & kBitMask);
    indexB = (x >> (11 * kWordSize) & kBitMask);
    indexC = (x >> (12 * kWordSize) & kBitMask);
    indexD = (x >> (13 * kWordSize) & kBitMask);
    indexE = (x >> (14 * kWordSize) & kBitMask);
    indexF = (x >> (15 * kWordSize) & kBitMask);
#if 0
    shift0 = (15 * kWordSize); 
    shift1 = (14 * kWordSize);
    shift2 = (13 * kWordSize);
    shift3 = (12 * kWordSize);
    shift4 = (11 * kWordSize);
    shift5 = (10 * kWordSize);
    shift6 = ( 9 * kWordSize);
    shift7 = ( 8 * kWordSize);
    shift8 = ( 7 * kWordSize);
    shift9 = ( 6 * kWordSize);
    shiftA = ( 5 * kWordSize);
    shiftB = ( 4 * kWordSize);
    shiftC = ( 3 * kWordSize);
    shiftD = ( 2 * kWordSize);
    shiftE = ( 1 * kWordSize);
    shiftF = ( 0 * kWordSize);
    
    valF = (precomputed_bit_reversal[index0] << (shift0)); 
    valE = (precomputed_bit_reversal[index1] << (shift1));
    valD = (precomputed_bit_reversal[index2] << (shift2));
    valC = (precomputed_bit_reversal[index3] << (shift3));
    valB = (precomputed_bit_reversal[index4] << (shift4));
    valA = (precomputed_bit_reversal[index5] << (shift5));
    val9 = (precomputed_bit_reversal[index6] << (shift6));
    val8 = (precomputed_bit_reversal[index7] << (shift7));
    val7 = (precomputed_bit_reversal[index8] << (shift8));
    val6 = (precomputed_bit_reversal[index9] << (shift9));
    val5 = (precomputed_bit_reversal[indexA] << (shiftA));
    val4 = (precomputed_bit_reversal[indexB] << (shiftB));
    val3 = (precomputed_bit_reversal[indexC] << (shiftC));
    val2 = (precomputed_bit_reversal[indexD] << (shiftD));
    val1 = (precomputed_bit_reversal[indexE] << (shiftE));
    val0 = (precomputed_bit_reversal[indexF] << (shiftF));

    printf("x     : %016llx\n", x);
    printf("index0: %x => %llx == LSL %02d ==> %016llx\n", index0, precomputed_bit_reversal[index0], shift0, valF);
    printf("index1: %x => %llx == LSL %02d ==> %016llx\n", index1, precomputed_bit_reversal[index1], shift1, valE);
    printf("index2: %x => %llx == LSL %02d ==> %016llx\n", index2, precomputed_bit_reversal[index2], shift2, valD);
    printf("index3: %x => %llx == LSL %02d ==> %016llx\n", index3, precomputed_bit_reversal[index3], shift3, valC);
    printf("index4: %x => %llx == LSL %02d ==> %016llx\n", index4, precomputed_bit_reversal[index4], shift4, valB);
    printf("index5: %x => %llx == LSL %02d ==> %016llx\n", index5, precomputed_bit_reversal[index5], shift5, valA);
    printf("index6: %x => %llx == LSL %02d ==> %016llx\n", index6, precomputed_bit_reversal[index6], shift6, val9);
    printf("index7: %x => %llx == LSL %02d ==> %016llx\n", index7, precomputed_bit_reversal[index7], shift7, val8);
    printf("index8: %x => %llx == LSL %02d ==> %016llx\n", index8, precomputed_bit_reversal[index8], shift8, val7);
    printf("index9: %x => %llx == LSL %02d ==> %016llx\n", index9, precomputed_bit_reversal[index9], shift9, val6);
    printf("indexA: %x => %llx == LSL %02d ==> %016llx\n", indexA, precomputed_bit_reversal[indexA], shiftA, val5);
    printf("indexB: %x => %llx == LSL %02d ==> %016llx\n", indexB, precomputed_bit_reversal[indexB], shiftB, val4);
    printf("indexC: %x => %llx == LSL %02d ==> %016llx\n", indexC, precomputed_bit_reversal[indexC], shiftC, val3);
    printf("indexD: %x => %llx == LSL %02d ==> %016llx\n", indexD, precomputed_bit_reversal[indexD], shiftD, val2);
    printf("indexE: %x => %llx == LSL %02d ==> %016llx\n", indexE, precomputed_bit_reversal[indexE], shiftE, val1);
    printf("indexF: %x => %llx == LSL %02d ==> %016llx\n", indexF, precomputed_bit_reversal[indexF], shiftF, val0);
#endif
    or_sum = (  (precomputed_bit_reversal[index0] << (15 * kWordSize)) |
                (precomputed_bit_reversal[index1] << (14 * kWordSize)) |
                (precomputed_bit_reversal[index2] << (13 * kWordSize)) |
                (precomputed_bit_reversal[index3] << (12 * kWordSize)) |
                (precomputed_bit_reversal[index4] << (11 * kWordSize)) |
                (precomputed_bit_reversal[index5] << (10 * kWordSize)) |
                (precomputed_bit_reversal[index6] << ( 9 * kWordSize)) |
                (precomputed_bit_reversal[index7] << ( 8 * kWordSize)) |
                (precomputed_bit_reversal[index8] << ( 7 * kWordSize)) |
                (precomputed_bit_reversal[index9] << ( 6 * kWordSize)) |
                (precomputed_bit_reversal[indexA] << ( 5 * kWordSize)) |
                (precomputed_bit_reversal[indexB] << ( 4 * kWordSize)) |
                (precomputed_bit_reversal[indexC] << ( 3 * kWordSize)) |
                (precomputed_bit_reversal[indexD] << ( 2 * kWordSize)) |
                (precomputed_bit_reversal[indexE] << ( 1 * kWordSize)) |
                (precomputed_bit_reversal[indexF] << ( 0 * kWordSize)) );

    printf("or      :  %016llx\n", or_sum);
               
    return or_sum;
}

int main()
{
    uint64_t x, y;
    //x = 0x8080808010101010;
    //printf("reverse(%016llx) => %016llx\n", x, reverse(x));
    x = 0x0FEDCBA987654321;
    printf("reverse(%016llx) => %016llx\n", x, reverse_lut(x));
}
