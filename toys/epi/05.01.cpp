#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

/*
 * odd parity is 1, even parity is 0
 */
short Parity1(unsigned long long x)
{
    short result = 0;
    while (x) {
        result ^= (x & 1);
        x >>= 1;
    }
    return result;
}

short Parity2(unsigned long long x)
{
    short result = 0;
    while (x) {
        result ^= 1;
        x &= (x - 1); // drops lowest set bit
    }
    return result;
}

                                     /* bit counts for 0..F */
unsigned int precomputed_parity[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
short Parity3(unsigned long long x)
{
    unsigned short count, bit_count, parity;
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

    cout << "x:      " << std::hex << x  << endl;
    cout << "index0: " << index0 << " => " << precomputed_parity[index0] << endl;
    cout << "index1: " << index1 << " => " << precomputed_parity[index1] << endl;
    cout << "index2: " << index2 << " => " << precomputed_parity[index2] << endl;
    cout << "index3: " << index3 << " => " << precomputed_parity[index3] << endl;
    cout << "index4: " << index4 << " => " << precomputed_parity[index4] << endl;
    cout << "index5: " << index5 << " => " << precomputed_parity[index5] << endl;
    cout << "index6: " << index6 << " => " << precomputed_parity[index6] << endl;
    cout << "index7: " << index7 << " => " << precomputed_parity[index7] << endl;
    cout << "index8: " << index8 << " => " << precomputed_parity[index8] << endl;
    cout << "index9: " << index9 << " => " << precomputed_parity[index9] << endl;
    cout << "indexA: " << indexA << " => " << precomputed_parity[indexA] << endl;
    cout << "indexB: " << indexB << " => " << precomputed_parity[indexB] << endl;
    cout << "indexC: " << indexC << " => " << precomputed_parity[indexC] << endl;
    cout << "indexD: " << indexD << " => " << precomputed_parity[indexD] << endl;
    cout << "indexE: " << indexE << " => " << precomputed_parity[indexE] << endl;
    cout << "indexF: " << indexF << " => " << precomputed_parity[indexF] << endl;

    count = (precomputed_parity[index0] ^
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

    parity = count & 1;
    cout << "bit_count: " << std::dec << bit_count << endl;
    cout << "parity   : " << std::dec << parity << endl;
               
    return count & 0x1;
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
    for (int i = 0; i < 16; i++) {
        cout << "[" << std::hex <<i <<"] = " << precomputed_parity[i] << endl;
    }
}
int main()
{
//    unsigned long long x = 0x3, running = 0;
//    for (x = 0; x < 14; x++) {
//        cout << "parity of: " << std::hex << x << " is " << Parity3(x) << endl;
//        running ^= Parity3(x);
//    }
//    cout << "running parity: " << running << endl;
    dump_parity();
    cout << "parity = " << std::hex << Parity3(0xabce123422334544) << endl;
    return 0;
}
