import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        Random generator = new Random();
        System.out.println("hello, world!".length());
        System.out.println("hello, world!");
        System.out.println("random: " + generator.nextInt() % 100);
    }
}
