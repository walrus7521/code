using System;

/*
 * odd parity is 1, even parity is 0
 * odd parity happens for odd number of bits
 * and also if the xor sum is odd.
 */

class p05_01
{

    /* this works
     * http://stackoverflow.com/questions/9133279/bitparity-finding-odd-number-of-bits-in-an-integer
     */
    int Parity5(int x)
    {
        x ^= x >> 32;
        x ^= x >> 16;
        x ^= x >>  8;
        x ^= x >>  4;
        x ^= x >>  2;
        x ^= x >>  1;
        x &=     0x1;
        return x;
    }

    static void test()
    {
        int t, x = 0xc10;
        int parity = 0;
        t = x;
        while (x != 0) {
            Console.WriteLine("x = " + x);
            parity ^= 1;
            x &= (x - 1); // drops lowest set bit
        }
        Console.WriteLine("parity of " + t + "is " + parity);
    }

    static int Main()
    {
        //int x = 0x3, running = 0;
        //for (x = 0; x < 14; x++) {
        //    Console.WriteLine("parity of: %x is %x", x, Parity5(x));
        //    running ^= Parity5(x);
        //}
        //Console.WriteLine("running parity: %x", running);
        test();
        return 0;
    }
}
