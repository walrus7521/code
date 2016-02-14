public class p05_01 {

    static long Parity(long x) {
        x ^= x >> 32;
        x ^= x >> 16;
        x ^= x >>  8;
        x ^= x >>  4;
        x ^= x >>  2;
        x ^= x >>  1;
        x &=     0x1;
        return x;
    }

    public static void main(String[] args) {
        System.out.format("parity = %x\n", Parity(0xabce1235));
    }
}
