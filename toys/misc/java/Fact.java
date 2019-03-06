import java.util.Scanner;
import java.math.BigInteger;


class Fact {

    final static int fact_of = 25;

    public static void main(String[] args) {
        BigInteger fac = BigInteger.ONE;
        for (int i = 2; i <= fact_of; i++) {
            fac = fac.multiply(BigInteger.valueOf(i));
        }
        System.out.println(fac);
    }
}

